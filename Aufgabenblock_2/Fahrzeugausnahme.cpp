#include "Fahrzeugausnahme.h"
#include "Fahrzeug.h"

VehicleException::VehicleException(Vehicle &vehicle, Weg &weg)
    : m_vehicle(vehicle), p_Weg(weg) {}

void StartException::handleException() const {
  std::unique_ptr<Vehicle> fahrzeug = p_Weg.pAbgabe(m_vehicle);
  if (fahrzeug) {
    // 重新将该车辆添加为行驶车辆
    std::cout << "Warning ：车辆 " << m_vehicle.getName() << " 在路径 "
              << p_Weg.getName() << " 上启动了。" << std::endl;
    p_Weg.vAnnahme(std::move(fahrzeug));
  } else {
    std::cerr << "错误：无法启动车辆 " << m_vehicle.getName() << "。"
              << std::endl;
  }
}

void EndOfPathException::handleException() const {
  std::unique_ptr<Vehicle> removedVehicle = p_Weg.pAbgabe(m_vehicle);
  if (!removedVehicle) {
    std::cerr << "错误：无法删除车辆 " << m_vehicle.getName() << "。"
              << std::endl;
  } else {
    std::cout << "Warning: 车辆 " << m_vehicle.getName() << " 到达了路径 "
              << p_Weg.getName() << " 的终点，已将其移出行驶列表。"
              << std::endl;
  }
  removedVehicle->drawPath(p_Weg); // 绘制车辆
}
