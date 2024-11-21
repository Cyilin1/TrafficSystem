//
// Created by Cyilin on 24-10-9.
//

#include "Fahrzeug.h"
#include "Fahren.h"
#include "Fahrzeugausnahme.h"
#include "Parken.h"

Vehicle::Vehicle() : Simulationsobjekt() {}

Vehicle::Vehicle(const std::string &name, double maxGeschwindigkeit)
    : Simulationsobjekt(name),
      m_maxSpeed((maxGeschwindigkeit > 0) ? maxGeschwindigkeit
                                          : 0), // 保证最大速度为正值
      m_totalDistance(0), m_runingTime(0) {}

void Vehicle::vAusgeben() const {
  Simulationsobjekt::vAusgeben();
  std::cout << std::resetiosflags(std::ios::adjustfield)
            << std::setiosflags(std::ios::left);
  // 设置输出列宽和精度，与表头的列宽一致
  std::cout << std::setw(10) << std::fixed << std::setprecision(2)
            << dGeschwindigkeit() << std::setw(10) << std::fixed
            << std::setprecision(2) << m_totalDistance;
}

void Vehicle::vAusgeben(std::ostream &os) const {
  Simulationsobjekt::vAusgeben();
  os << std::setw(10) << std::fixed << std::setprecision(2)
     << dGeschwindigkeit() << " | " << std::setw(10) << std::fixed
     << std::setprecision(2) << m_totalDistance << " | ";
}

void Vehicle::vKopf() {
  Simulationsobjekt::vKopf();
  std::cout << std::setw(10) << "Max Speed" << " | " << std::setw(10)
            << "Mileage" << " | " << std::setw(10) << "Fuel" << std::setw(15)
            << "Current Speed" << std::endl;
  std::cout << "-------------------------------------------------------"
            << std::endl;
}

void Vehicle::vSimulieren() {
  if (m_behavior) {
    //    double dAktuelleGeschwindigkeit = dGeschwindigkeit();
    double dZeitDelta = d_GlobaleZeit - p_dZeit;
    if (dZeitDelta <= 0)
      return;
    //    double dGefahreneStrecke = dAktuelleGeschwindigkeit * dZeitDelta;
    double dGefahreneStrecke = m_behavior->dStrecke(*this, dZeitDelta);

    // 更新总行驶距离和总时间
    m_currDistance += dGefahreneStrecke; // 更新当前路径上的行驶距离
    m_totalDistance += dGefahreneStrecke;
    m_runingTime += dZeitDelta;
    p_dZeit = d_GlobaleZeit;

    //    // 检查是否需要抛出异常
    //    if (p_dAbschnittStrecke >= p_pVerhalten->getWeg().getLaenge()) {
    //      throw Streckenende(*this, p_pVerhalten->getWeg());
    //      //  抛出到达终点异常
    //    }
  }
}

void Vehicle::vNeueStrecke(Weg &weg) {
  m_behavior = std::make_unique<Fahren>(weg); // 设置为行驶行为
  std::cout << "Vehicle " << getName() << " 被添加到路径 " << weg.getName()
            << " 上。\n";
  m_currDistance = 0.0; // 重置当前路径的行驶距离
}

void Vehicle::vNeueStrecke(Weg &weg, double dStartzeit) {
  m_behavior = std::make_unique<Parken>(weg, dStartzeit); // 设置为停放行为
  m_currDistance = 0.0; // 重置当前路径的行驶距离
}

double Vehicle::dGeschwindigkeit() const { return m_maxSpeed; }

void Vehicle::vLosfahren() {
  throw StartException(*this, m_behavior->getWeg()); // 抛出启动异常
}
