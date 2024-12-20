#ifndef FAHREN_H
#define FAHREN_H

#include "Verhalten.h"
class Fahrzeug;

class Fahren : public Verhalten {
public:
  Fahren(Weg &weg) : Verhalten(weg) {}

  // 行驶时计算行驶的距离
  double dStrecke(Fahrzeug &fahrzeug, double dZeitIntervall) override;
};

#endif // FAHREN_H
