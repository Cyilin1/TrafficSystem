//
// Created by Cyilin on 24-10-9.
//

#include "Fahrzeug.h"

Fahrzeug::Fahrzeug() : Simulationsobjekt() {}

Fahrzeug::Fahrzeug(const std::string &name, double maxGeschwindigkeit)
    : Simulationsobjekt(name),
      p_dMaxGeschwindigkeit((maxGeschwindigkeit > 0) ? maxGeschwindigkeit
                                                     : 0), // 保证最大速度为正值
      p_dGesamtstrecke(0), p_dGesamtZeit(0) {}

void Fahrzeug::vAusgeben() const {
  Simulationsobjekt::vAusgeben();
  std::cout << std::resetiosflags(std::ios::adjustfield)
            << std::setiosflags(std::ios::left);
  // 设置输出列宽和精度，与表头的列宽一致
  std::cout << std::setw(10) << std::fixed << std::setprecision(2)
            << dGeschwindigkeit() << std::setw(10) << std::fixed
            << std::setprecision(2) << p_dGesamtstrecke;
}

void Fahrzeug::vAusgeben(std::ostream &os) const {
  Simulationsobjekt::vAusgeben();
  os << std::resetiosflags(std::ios::adjustfield)
     << std::setiosflags(std::ios::left);
  os << std::setw(10) << std::fixed << std::setprecision(2)
     << dGeschwindigkeit() << std::setw(10) << std::fixed
     << std::setprecision(2) << p_dGesamtstrecke;
}

void Fahrzeug::vKopf() {
  std::cout << std::resetiosflags(std::ios::adjustfield)
            << std::setiosflags(std::ios::left);
  std::cout << std::setw(5) << "ID" << std::setw(10) << "Name" << std::setw(10)
            << "Max Speed" << std::setw(10) << "Mileage" << std::setw(10)
            << "Fuel" << std::setw(15) << "Current Speed" << std::endl;
  std::cout << "-------------------------------------------------------"
            << std::endl;
}

void Fahrzeug::vSimulieren() {
  double dAktuelleGeschwindigkeit = dGeschwindigkeit();
  double dZeitDelta = d_GlobaleZeit - p_dZeit;
  if (dZeitDelta <= 0)
    return;
  double dGefahreneStrecke = dAktuelleGeschwindigkeit * dZeitDelta;

  // 更新总行驶距离和总时间
  p_dGesamtstrecke += dGefahreneStrecke;
  p_dGesamtZeit += dZeitDelta;
  p_dZeit = d_GlobaleZeit;
}

double Fahrzeug::dGeschwindigkeit() const { return p_dMaxGeschwindigkeit; }
