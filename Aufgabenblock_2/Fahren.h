#ifndef FAHREN_H
#define FAHREN_H

#include "Verhalten.h"
class Vehicle;

class Fahren : public Verhalten {
public:
  Fahren(Weg &weg) : Verhalten(weg) {}

  // 行驶时计算行驶的距离
  double dStrecke(Vehicle &fahrzeug, double dZeitIntervall) override;
};

#endif // FAHREN_H
