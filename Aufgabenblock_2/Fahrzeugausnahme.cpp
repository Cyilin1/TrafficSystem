#include "Fahrzeugausnahme.h"
#include "Fahrzeug.h"

Fahrzeugausnahme::Fahrzeugausnahme(Vehicle &fzg, Weg &weg)
    : p_Fahrzeug(fzg), p_Weg(weg) {}

void Losfahren::vBearbeiten() const {
  std::unique_ptr<Vehicle> fahrzeug = p_Weg.pAbgabe(p_Fahrzeug);
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

void Streckenende::vBearbeiten() const {
  std::unique_ptr<Vehicle> removedVehicle = p_Weg.pAbgabe(p_Fahrzeug);
  if (!removedVehicle) {
    std::cerr << "错误：无法删除车辆 " << p_Fahrzeug.getName() << "。"
              << std::endl;
  } else {
    std::cout << "Warning: 车辆 " << p_Fahrzeug.getName() << " 到达了路径 "
              << p_Weg.getName() << " 的终点，已将其移出行驶列表。"
              << std::endl;
  }
  removedVehicle->vZeichnen(p_Weg); // 绘制车辆
}
