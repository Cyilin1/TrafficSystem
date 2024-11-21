#ifndef FAHRRAD_H
#define FAHRRAD_H

#include "Fahrzeug.h"

class Fahrrad : public Vehicle {
public:
  Fahrrad(const std::string &name = "", double maxGeschwindigkeit = 0.0);

  virtual void executeSimulation() override;
  virtual void displayData() const override;
  virtual void displayData(std::ostream &os) const override;
  virtual void drawPath(const Weg &weg) const override;
  virtual double
  dTanken(double dMenge = std::numeric_limits<double>::infinity()) override {
    return 0.0; // 自行车无油箱，不能加油
  }
  virtual double getMaxSpeed() const override;
};

#endif // FAHRRAD_H
