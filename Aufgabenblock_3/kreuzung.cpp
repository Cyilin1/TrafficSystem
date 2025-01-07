#include "kreuzung.h"
#include "Fahrzeug.h"
#include "pkw.h"
#include <algorithm>  // for std::find
#include <random>

std::ostream& operator<<( std::ostream& os, const Fahrzeug& fahrzeug ) {
    fahrzeug.vAusgeben( os );
    return os;
}

std::ostream& operator<<( std::ostream& os, const Weg& fahrzeug ) {
    fahrzeug.vAusgeben( os );
    return os;
}
/**
 * @brief Kreuzung::vVerbind 连接两个十字路口
 * @param sNamein 去程Weg
 * @param sNameout 返程Weg
 * @param length 路径长度
 * @param start 开始的十字路口
 * @param end 结束的十字路口
 * @param tempolimit 限速
 * @param ueberholverbot 超车禁令
 */
void Kreuzung::vVerbinde( const std::string& sNameHin, const std::string& sNameRueck, double dLaenge, std::shared_ptr< Kreuzung > pStartKreuzung, std::shared_ptr< Kreuzung > pEndKreuzung,
                          Tempolimit eTempolimit, bool bUeberholverbot ) {
    // 创建去程路段
    auto pWegHin = std::make_shared< Weg >( sNameHin, dLaenge, pStartKreuzung, pEndKreuzung, eTempolimit, bUeberholverbot );
    // 创建返程路段
    auto pWegRueck = std::make_shared< Weg >( sNameRueck, dLaenge, pEndKreuzung, pStartKreuzung, eTempolimit, bUeberholverbot );

    // 设置彼此为返程路段
    pWegHin->setOppositeWeg( pWegRueck );
    pWegRueck->setOppositeWeg( pWegHin );

    // 将去程路段添加到起点十字路口
    pStartKreuzung->vAnnahme( pWegHin );

    // 将返程路段添加到终点十字路口
    pEndKreuzung->vAnnahme( pWegRueck );
}

void Kreuzung::vAnnahme( std::shared_ptr< Weg > pWeg ) {
    p_Weg.push_back( std::move( pWeg ) );
}

Kreuzung::Kreuzung( const std::string& sName, double dTankstelle ) : Simulationsobjekt( sName ), pdTankstelle( dTankstelle ) {}

double Kreuzung::dTanken( Fahrzeug& fzg ) {
    // 检查是否是 PKW 类型
    PKW* pPKW = dynamic_cast< PKW* >( &fzg );
    if ( !pPKW ) {
        // 如果不是 PKW 类型，不进行加油
        std::cout << "Fahrzeug " << fzg.getName() << " 不是 PKW，不需要加油。" << std::endl;
        return 0.0;
    }

    // 计算车辆可以加的油量
    double dTankinhalt      = pPKW->getTankinhalt();
    double dMaxTank         = pPKW->getTankvolumen();
    double dBenoetigteMenge = dMaxTank - dTankinhalt;

    if ( dBenoetigteMenge <= 0.0 ) {
        // 油箱已满
        std::cout << "PKW " << pPKW->getName() << " 油箱已满，不需要加油。" << std::endl;
        return 0.0;
    }

    // 确定实际加的油量
    double dTatsaechlichGetankt = std::min( dBenoetigteMenge, pdTankstelle );

    // 减少加油站的油量
    pdTankstelle -= dTatsaechlichGetankt;

    // 给车辆加油
    pPKW->dTanken( dTatsaechlichGetankt );

    // 输出加油信息
    std::cout << "PKW " << pPKW->getName() << " 加油 " << dTatsaechlichGetankt << " 升，加油站剩余油量：" << pdTankstelle << " 升。" << std::endl;

    // 返回实际加的油量
    return dTatsaechlichGetankt;
}

void Kreuzung::vAnnahme( std::unique_ptr< Fahrzeug > fahrzeug, double dStartzeit ) {
    // 检查是否有发出的路段
    if ( p_Weg.empty() ) {
        std::cerr << "错误：十字路口 " << getName() << " 没有发出的路段！" << std::endl;
        return;
    }

    dTanken( *fahrzeug );

    // 获取第一个发出的路段
    Weg* pErsterWeg = p_Weg.front().get();
    if ( !pErsterWeg ) {
        std::cerr << "错误：十字路口 " << getName() << " 的第一个路段无效！" << std::endl;
        return;
    }

    // 将车辆停放在第一个路段上
    if ( dStartzeit == 0.0 ) {
        pErsterWeg->vAnnahme( std::move( fahrzeug ) );
        return;
    }
    pErsterWeg->vAnnahme( std::move( fahrzeug ), dStartzeit );
}

void Kreuzung::vSimulieren() {
    std::cout << "仿真十字路口 " << getName() << " 的所有路段：" << std::endl;
    // 遍历所有发出的路段
    for ( auto& weg : p_Weg ) {
        if ( weg ) {
            weg->vSimulieren();  // 调用每条路段的仿真函数
            if ( !weg->getFahrzeuge().empty() ) {
                Fahrzeug::vKopf();
                for ( auto& fahrzeug : weg->getFahrzeuge() ) {
                    std::cout << *fahrzeug;
                    std::cout << std::endl;
                }
                std::cout << "==================车辆信息Finished==================" << std::endl;
            }
        }
        else {
            std::cerr << "警告：十字路口 " << getName() << " 包含无效的路段指针。" << std::endl;
        }
        if ( !weg->getFahrzeuge().empty() ) {
            Weg::vKopf();
            std::cout << *weg << std::endl;
            std::cout << "==================================" << std::endl;
            std::cout << "==================================" << std::endl;
        }
    }
}

std::shared_ptr< Weg > Kreuzung::pZufaelligerWeg( Weg& einfahrWeg ) {
    if ( p_Weg.empty() ) {
        return nullptr;
    }

    std::vector< std::shared_ptr< Weg > > chooseWeg;
    for ( const auto& weg : p_Weg ) {
        if ( weg && weg->getOppositeWeg().get() != &einfahrWeg ) {
            chooseWeg.push_back( weg );
        }
    }

    if ( !chooseWeg.empty() ) {
        static std::random_device               rd;
        static std::mt19937                     gen( rd() );
        std::uniform_int_distribution< size_t > dist( 0, chooseWeg.size() - 1 );
        return chooseWeg[ dist( gen ) ];
    }
    // 死活同
    return einfahrWeg.getOppositeWeg();
}
