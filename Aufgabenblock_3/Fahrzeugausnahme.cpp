#include "Fahrzeugausnahme.h"
#include "Fahrzeug.h"
#include "Weg.h"
#include "kreuzung.h"

// std::ostream& operator<<( std::ostream& os, const Weg& fahrzeug ) {
//     fahrzeug.vAusgeben( os );
//     return os;
// }

Fahrzeugausnahme::Fahrzeugausnahme(Fahrzeug &fzg, Weg &weg)
    : p_Fahrzeug(fzg), p_Weg(weg) {}

void Losfahren::vBearbeiten() const {
  std::unique_ptr<Fahrzeug> fahrzeug = p_Weg.pAbgabe(p_Fahrzeug);
  if (fahrzeug) {
    // 重新将该车辆添加为行驶车辆
    std::cout << "Warning ：车辆 " << p_Fahrzeug.getName() << " 在路径 "
              << p_Weg.getName() << " 上启动了。" << std::endl;
    p_Weg.vAnnahme(std::move(fahrzeug));
  } else {
    std::cerr << "错误：无法启动车辆 " << p_Fahrzeug.getName() << "。"
              << std::endl;
  }
}

// 将此功能集成到路段终点的处理函数中，
// 使到达路段末尾的车辆可以被设置为行驶状态，
// 并转移到所选的路段上。在此过程中，车辆也应被加满油。

void Streckenende::vBearbeiten() const {
  std::unique_ptr< Fahrzeug > removedVehicle = p_Weg.pAbgabe( p_Fahrzeug );
  //  std::cout << p_Weg << std::endl;
  if (!removedVehicle) {
    std::cerr << "错误：无法删除车辆 " << p_Fahrzeug.getName() << "。"
              << std::endl;
  } else {
    std::cout << "Warning: 车辆 " << p_Fahrzeug.getName() << " 到达了路径 "
              << p_Weg.getName() << " 的终点，已将其移出行驶列表。"
              << std::endl;
  }
  removedVehicle->vZeichnen( p_Weg );  // 绘制车辆

  // 获取目标的十字路口
  auto endKreuzung = p_Weg.getEndKreuzung();
  if ( !endKreuzung ) {
    std::cerr << "error" << std::endl;
  }

  double dGetTank = endKreuzung->dTanken( *removedVehicle );
  std::cout << removedVehicle->getName() << "已经加油" << dGetTank << "升!" << std::endl;

  auto destWeg = endKreuzung->pZufaelligerWeg( p_Weg );
  if ( !destWeg ) {
    std::cerr << "error" << std::endl;
  }

  // 时间：[转移的时间点]
  // 十字路口：[十字路口名称] [加油站的剩余油量]
  // 更换：[旧路段名称] → [新路段名称]
  // 车辆：[车辆信息]
  std::cout << "Time :" << d_GlobaleZeit << std::endl;
  std::cout << "Kreuzung :" << endKreuzung->getRemainingFuel() << std::endl;
  std::cout << "Alter :" << p_Weg.getName() << destWeg->getName() << std::endl;
  std::cout << "Fahrzeug :" << removedVehicle << std::endl;
  destWeg->vAnnahme( std::move( removedVehicle ) );
}
