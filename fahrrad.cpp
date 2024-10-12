#include "fahrrad.h"
#include <iostream>

Fahrrad::Fahrrad(const std::string &name, double maxGeschwindigkeit)
    : Fahrzeug(name, maxGeschwindigkeit) {}

void Fahrrad::vSimulieren() {
  double zeitDifferenz = d_GlobaleZeit - p_dZeit;

  if (zeitDifferenz > 0) {
    double effektiveGeschwindigkeit = dGeschwindigkeit();
    p_dGesamtstrecke += zeitDifferenz * effektiveGeschwindigkeit;
    p_dGesamtZeit += zeitDifferenz;
    p_dZeit = d_GlobaleZeit;
  }
}

void Fahrrad::vAusgeben() const {
  Fahrzeug::vAusgeben();
  std::cout << std::setw(10) << "-" << std::setw(15) << dGeschwindigkeit();
}

double Fahrrad::dGeschwindigkeit() const {
  double dCurrentSpeed = p_dMaxGeschwindigkeit;
  double dDistance = p_dGesamtstrecke;

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
