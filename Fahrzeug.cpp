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

void Fahrzeug::vSimulieren() {
  double zeitDifferenz = d_GlobaleZeit - p_dZeit;
  if (zeitDifferenz > 0) {
    p_dGesamtstrecke += zeitDifferenz * p_dMaxGeschwindigkeit;
    p_dGesamtZeit += zeitDifferenz;
    p_dZeit = d_GlobaleZeit;
  }
}
