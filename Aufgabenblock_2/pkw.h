#ifndef PKW_H
#define PKW_H

#include "Fahrzeug.h"

class PKW : public Vehicle {
public:
  PKW(const std::string &name = "", double maxspeed = 0.0,
      double consumptionPerKm = 0.0, double tankCapacity = 50.0);

  virtual void executeSimulation() override;
  virtual void displayData() const override;
  virtual void displayData(std::ostream &os) const override;
  virtual double getMaxSpeed() const override;

  // 汽车特有行为
  virtual double
  fillTank(double dMenge = std::numeric_limits<double>::infinity()) override;
  virtual void drawPath(const Weg &weg) const override;

private:
  double m_consumptionPerKm; // 每公里油耗
  double m_tankCapacity;     // 最大油箱容量
  double m_currentFuel;      // 当前油量
};

#endif // PKW_H
