#include "pkw.h"
#include "Fahrzeugausnahme.h"
#include "SimuClient.h"

PKW::PKW(const std::string &name, double maxspeed, double consumptionPerKm,
         double tankCapacity)
    : Vehicle(name, maxspeed), m_consumptionPerKm(consumptionPerKm),
      m_tankCapacity(tankCapacity), m_currentFuel(tankCapacity / 2.0) {
  // 油箱中的油量初始化为油箱容量的一半
}

void PKW::executeSimulation() {
  if (!m_behavior)
    return;
  double dZeitDelta = globalTime - p_dZeit;
  if (dZeitDelta <= 0)
    return;
  double dGefahreneStrecke = m_behavior->calculateDistance(*this, dZeitDelta);
  // 计算所需油量
  double dBenotigteMenge = (dGefahreneStrecke / 100.0) * m_consumptionPerKm;

  // 如果油量不足，车辆只能行驶部分距离
  if (dBenotigteMenge > m_currentFuel) {
    dGefahreneStrecke = (m_currentFuel / m_consumptionPerKm) * 100.0;
    m_currentFuel = 0; // 油量耗尽
  } else {
    m_currentFuel -= dBenotigteMenge;
  }

  // 更新总行驶距离和总行驶时间
  m_currDistance += dGefahreneStrecke; // 更新当前路径上的行驶距离
  m_totalDistance += dGefahreneStrecke;
  m_runingTime += dZeitDelta;
  p_dZeit = globalTime;
  // 检查是否需要抛出异常
  if (m_currDistance >= m_behavior->getWeg().getLaenge()) {
    throw EndOfPathException(*this, m_behavior->getWeg());
    //  抛出到达终点异常
  }
}

void PKW::displayData() const {
  Vehicle::displayData();
  std::cout << std::setw(10) << m_currentFuel << std::setw(15) << getMaxSpeed();
}

void PKW::displayData(std::ostream &os) const {
  Vehicle::displayData(os);
  os << std::setw(10) << m_currentFuel << std::setw(15) << getMaxSpeed();
}

double PKW::fillTank(double dMenge) {
  if (dMenge == std::numeric_limits<double>::infinity()) {
    dMenge = m_tankCapacity - m_currentFuel;
  }

  double tatsaechlicheMenge = std::min(dMenge, m_tankCapacity - m_currentFuel);
  m_currentFuel += tatsaechlicheMenge;

  // 返回实际加的油量
  return tatsaechlicheMenge;
}

void PKW::drawPath(const Weg &weg) const {
  double relPosition = m_totalDistance / weg.getLaenge(); // 计算相对位置
  double kmH = this->getMaxSpeed();                       // 获取车辆速度
  double tank = m_currentFuel;                            // 获取油箱剩余量
  bZeichnePKW(this->getName(), weg.getName(), relPosition, kmH, tank);
}

double PKW::getMaxSpeed() const {
  if (m_behavior) {
    double wegTempolimit = m_behavior->getWeg().getTempolimit();
    //    if (maxGeschwindigkeit > wegTempolimit) {
    //      std::cout << "超过限速，进行降速操作！！" << std::endl;
    //      maxGeschwindigkeit = wegTempolimit;
    //    }
    return std::min(m_maxSpeed, wegTempolimit); // 取最小值
  }
  return m_maxSpeed;
}
