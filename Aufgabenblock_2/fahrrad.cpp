#include "fahrrad.h"
#include "Fahrzeugausnahme.h"
#include "SimuClient.h"
#include <iostream>

Bicycle::Bicycle(const std::string &name, double maxSpeed)
    : Vehicle(name, maxSpeed) {}

void Bicycle::executeSimulation() {
  if (!m_behavior)
    return;
  double dZeitDelta = globalTime - p_dZeit;
  if (dZeitDelta <= 0)
    return;

  double dGefahreneStrecke = m_behavior->calculateDistance(*this, dZeitDelta);

  // 更新总行驶距离和总行驶时间
  m_currDistance += dGefahreneStrecke; // 更新当前路径上的行驶距离
  m_totalDistance += dGefahreneStrecke;
  m_runingTime += dZeitDelta;
  p_dZeit = globalTime;
  //  // 检查是否需要抛出异常
  if (m_currDistance >= m_behavior->getWeg().getLaenge()) {
    throw EndOfPathException(*this, m_behavior->getWeg());
    //  抛出到达终点异常
  }
}

void Bicycle::displayData() const {
  Vehicle::displayData();
  std::cout << std::setw(10) << "-";
  //            << std::setw(15) << getMaxSpeed();
}

void Bicycle::displayData(std::ostream &os) const {
  Vehicle::displayData(os);
  os << std::setw(10) << "-";
  //     << std::setw(15) << getMaxSpeed();
}

void Bicycle::drawPath(const Weg &weg) const {
  double relPosition = m_totalDistance / weg.getLaenge(); // 计算相对位置
  double kmH = this->getMaxSpeed();                       // 获取自行车速度
  bZeichneFahrrad(this->getName(), weg.getName(), relPosition, kmH);
}

double Bicycle::getMaxSpeed() const {
  double dCurrentSpeed = m_maxSpeed;
  double dDistance = m_totalDistance;

  int numReductions = static_cast<int>(dDistance / 20.0);
  for (int i = 0; i < numReductions; ++i) {
    dCurrentSpeed *= 0.9;
  }

  // 速度最低不低于 12 公里/小时
  if (dCurrentSpeed < 12.0) {
    dCurrentSpeed = 12.0;
  }

  return dCurrentSpeed;
}
