#ifndef FAHRRAD_H
#define FAHRRAD_H

#include "Fahrzeug.h"

class Fahrrad : public Fahrzeug {
public:
  Fahrrad(const std::string &name = "", double maxGeschwindigkeit = 0.0);

  virtual void vSimulieren() override;
  virtual void vAusgeben() const override;
  virtual double
  dTanken(double dMenge = std::numeric_limits<double>::infinity()) override {
    return 0.0; // 自行车无油箱，不能加油
  }
  virtual double dGeschwindigkeit() const override;
};

#endif // FAHRRAD_H
