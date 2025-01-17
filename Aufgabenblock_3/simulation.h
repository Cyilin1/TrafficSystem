#ifndef SIMULATION_H
#define SIMULATION_H

#include "SimuClient.h"
#include "Weg.h"
#include "fahrrad.h"
#include "kreuzung.h"
#include "pkw.h"
#include <fstream>
#include <iostream>
#include <map>
#include <memory>
#include <sstream>
#include <stdexcept>
#include <string>

// KREUZUNG Kr1 800
// KREUZUNG Kr2 800
// KREUZUNG Kr3 800
// KREUZUNG Kr4 800
// KREUZUNG Kr5 800
// KREUZUNG Kr6 800
// KREUZUNG Kr7 800
// KREUZUNG Kr8 800
// STRASSE Kr1 Kr2 Weg12 Weg21 40 3 1
//     STRASSE Kr2 Kr2 Weg22a Weg22b 80 3 1
//     STRASSE Kr3 Kr3 Weg33a Weg33b 80 3 1
//     STRASSE Kr4 Kr5 Weg45b Weg54b 60 4 1
//     STRASSE Kr1 Kr6 Weg16 Weg61 220 2 0
//     STRASSE Kr1 Kr8 Weg18 Weg81 180 2 2
//     STRASSE Kr2 Kr5 Weg25 Weg52 40 1 1
//     STRASSE Kr5 Kr4 Weg54a Weg45a 60 3 1
//     STRASSE Kr5 Kr8 Weg58 Weg85 70 3 1
//     STRASSE Kr6 Kr7 Weg67 Weg76 50 3 1
//     STRASSE Kr7 Kr8 Weg78 Weg87 50 3 1
//     STRASSE Kr8 Kr6 Weg86 Weg68 120 3 1
//     STRASSE Kr5 Kr7 Weg57 Weg75 30 3 1
//     PKW BMW 220 10.2 80 Kr3 2.0     Line:21 : Kreuzung3 doesn't exist!
//     FAHRRAD Peugeot 40 Kr7 4
//     PKW Porsche 240 14.5 70 Kr7 3.3
//     FAHRRAD BMX 24 Kr1 1.5

class Simulation {
private:
    std::map< std::string, std::shared_ptr< Kreuzung > > kreuzungMap;
    // {"Kr1"(map->first) : xxxxxx(map->second), "Kr2" : xxxx }

public:
    Simulation();
    /**
     * @brief vAddKreuzung 添加一个十字路口到map里
     * @param name
     * @param kreuzung
     */
    void vAddKreuzung( const std::string& name, std::shared_ptr< Kreuzung > kreuzung ) {
        // 找得到，或者说原来的map中已有当前的十字路口
        if ( kreuzungMap.find( name ) != kreuzungMap.end() ) {
            throw std::runtime_error( "Duplicated Kreuzung : " + name );
        }
        // 找不到，那就添加到数据库中
        kreuzungMap[ name ] = kreuzung;
    }

    /**
     * @brief vFindKreuzung 给定一个十字路口的名字，找到对应的十字路口对象
     * @param name
     * @return
     */
    std::shared_ptr< Kreuzung > vFindKreuzung( const std::string name ) {
        auto it = kreuzungMap.find( name );
        // 如果找不到十字路口的话
        if ( it == kreuzungMap.end() ) {
            throw std::runtime_error( "Kreuzung doesn't exist!" );
        }
        return it->second;
    }

    /**
     * @brief vSimulieren
     * 整体的Simulation调用：先从当前Simulation类调用vSimulieren方法，再去调用Kreuzung中的Simulation，再去调研每个Weg的Simulation，再去调用每个Fahrzeug的Simulation
     * 实现思路：遍历kreuzungMap每一个十字路口，让每一个十字路口Simulation一下
     * @param dDauer
     * @param dZeitschritt
     */
    void vSimulieren( double dDauer, double dZeitschritt ) {
        for ( d_GlobaleZeit = 0; d_GlobaleZeit < dDauer; d_GlobaleZeit += dZeitschritt ) {
            vSetzeZeit( d_GlobaleZeit );
            std::cout << "Current Time : " << d_GlobaleZeit << std::endl;
            // 遍历kreuzungMap每一个十字路口
            for ( const auto& [ name, kreuzung ] : kreuzungMap ) {
                kreuzung->vSimulieren();
            }
            std::cout << "============================================================" << std::endl;
            vSleep( 1000 );  // 暂停2000毫秒
        }
        vBeendeGrafik();
        std::cout << "============================================================" << std::endl;
        std::cout << "Simulation End!" << std::endl;
    }

    /**
     * @brief 读取dat内的文件内容，一行一行去解析内容
     * @param is
     */
    void vEinlesen( std::istream& is, bool bMitGrafik = false ) {
        if ( bMitGrafik ) {
            // 初始化图形窗口
            const int windowWidth  = 1000;
            const int windowHeight = 1000;
            if ( !bInitialisiereGrafik( windowWidth, windowHeight ) ) {
                std::cerr << "图形界面初始化失败！" << std::endl;
                return;
            }
        }
        std::string line;
        int         lineNumber = 0;
        try {
            while ( std::getline( is, line ) ) {
                lineNumber++;
                // 读取第一个单词
                std::istringstream lineStream( line );
                std::string        keyword;
                lineStream >> keyword;
                if ( keyword == "STRASSE" ) {
                    //                STRASSE <NameQ> <NameZ> <NameW1> <NameW2> <长度> <速度限制> <超车禁令>
                    std::string NameQ, NameZ, NameW1, NameW2;
                    double      length;
                    int         tempolimit;
                    bool        ueberholverbot;
                    int         coordNum = 0;
                    lineStream >> NameQ >> NameZ >> NameW1 >> NameW2 >> length >> tempolimit >> ueberholverbot;
                    if ( bMitGrafik ) {
                        lineStream >> coordNum;
                        std::vector< int > koord( 2 * coordNum );
                        for ( int i = 0; i < koord.size(); i++ ) {
                            lineStream >> koord[ i ];
                        }
                        bZeichneStrasse( NameW1, NameW2, length, coordNum, koord.data() );
                    }
                    auto       kreuzungQ   = vFindKreuzung( NameQ );
                    auto       kreuzungZ   = vFindKreuzung( NameZ );
                    Tempolimit eTempolimit = static_cast< Tempolimit >( tempolimit );
                    Kreuzung::vVerbinde( NameW1, NameW2, length, kreuzungQ, kreuzungZ, eTempolimit, ueberholverbot );
                }
                else if ( keyword == "PKW" ) {
                    //                PKW <小汽车数据> <NameS> <出发时间>
                    auto        pkw = std::make_unique< PKW >();
                    std::string startKreuzung;
                    double      startZeit;
                    lineStream >> *pkw >> startKreuzung >> startZeit;
                    auto startKre = vFindKreuzung( startKreuzung );
                    startKre->vAnnahme( std::move( pkw ), startZeit );
                }
                else if ( keyword == "FAHRRAD" ) {
                    //                FAHRRAD <自行车数据> <NameS> <出发时间>
                    auto        fahrrad = std::make_unique< Fahrrad >();
                    std::string startKreuzung;
                    double      startZeit;
                    lineStream >> *fahrrad >> startKreuzung >> startZeit;
                    auto startKre = vFindKreuzung( startKreuzung );
                    startKre->vAnnahme( std::move( fahrrad ), startZeit );
                }
                else if ( keyword == "KREUZUNG" ) {
                    // KREUZUNG <十字路口数据>
                    auto kre = std::make_shared< Kreuzung >();
                    lineStream >> *kre;
                    double x = 0, y = 0;
                    if ( bMitGrafik ) {
                        lineStream >> x >> y;
                        bZeichneKreuzung( x, y );
                    }
                    vAddKreuzung( kre->getName(), kre );
                }
                else {
                    throw std::runtime_error( "Unknown Keyword : " + keyword );
                }
            }
        }
        catch ( const std::exception& ex ) {
            std::cerr << "Error : Line " << lineNumber << " failed!" << std::endl;
        }
    }
};

#endif // SIMULATION_H
