#ifndef PKW_H
#define PKW_H

#include "Fahrzeug.h"

class PKW : public Fahrzeug {
public:
  PKW(const std::string &name = "", double maxGeschwindigkeit = 0.0,
      double verbrauch = 0.0, double tankvolumen = 50.0);

  virtual void vSimulieren() override;
  virtual void vAusgeben() const override;
  virtual void vAusgeben(std::ostream &os) const override;
  virtual double dGeschwindigkeit() const override;

  // 汽车特有行为
  virtual double
  dTanken(double dMenge = std::numeric_limits<double>::infinity()) override;
  virtual void vZeichnen(const Weg &weg) const override;

private:
  double p_dVerbrauch;   // 每公里油耗
  double p_dTankvolumen; // 最大油箱容量
  double p_dTankinhalt;  // 当前油量
};

#endif // PKW_H
