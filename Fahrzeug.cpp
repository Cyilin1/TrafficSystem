//
// Created by Cyilin on 24-10-9.
//

#include "Fahrzeug.h"

Fahrzeug::Fahrzeug()
    : p_sName(""), p_iD(++p_iMaxID), p_dMaxGeschwindigkeit(0),
      p_dGesamtstrecke(0), p_dGesamtZeit(0), p_dZeit(0) {
  std::cout << "Fahrzeug created: Name=\"" << p_sName << "\", ID=" << p_iD
            << std::endl;
}

Fahrzeug::Fahrzeug(const std::string &name, double maxGeschwindigkeit)
    : p_sName(name), p_iD(++p_iMaxID),
      p_dMaxGeschwindigkeit((maxGeschwindigkeit > 0) ? maxGeschwindigkeit
                                                     : 0), // 保证最大速度为正值
      p_dGesamtstrecke(0), p_dGesamtZeit(0), p_dZeit(0) {
  std::cout << "Fahrzeug created: Name=\"" << p_sName << "\", ID=" << p_iD
            << " created, Max Speed: " << p_dMaxGeschwindigkeit << "km /h.\n ";
}

Fahrzeug::~Fahrzeug() {
  std::cout << "Fahrzeug destroyed: Name=\"" << p_sName << "\", ID=" << p_iD
            << std::endl;
}

void Fahrzeug::vKopf() {
  std::cout << std::left << std::setw(5) << "ID" << std::setw(10) << "名称"
            << std::setw(15) << "最大速度" << std::setw(10) << "总里程数"
            << std::setw(10) << "Fuel" << std::endl;
  std::cout << "--------------------------------------" << std::endl;
}

void Fahrzeug::vAusgeben() const {
  std::cout << std::left << std::setw(5) << p_iD << std::setw(10) << p_sName
            << std::setw(15) << std::fixed << std::setprecision(2)
            << dGeschwindigkeit() << std::setw(10) << std::fixed
            << std::setprecision(2) << p_dGesamtstrecke;
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
