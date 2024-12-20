#ifndef PARKEN_H
#define PARKEN_H

#include "Verhalten.h"

class Parken : public Verhalten {
public:
  Parken(Weg &weg, double dStartzeit)
      : Verhalten(weg), p_dStartzeit(dStartzeit) {}

  // 停放车辆，在达到启动时间之前返回 0.0
  double dStrecke(Fahrzeug &aFzg, double dZeitIntervall) override;

private:
  double p_dStartzeit;     // 停放开始时间
  bool bGestartet = false; // 记录是否已经启动
};

#endif // PARKEN_H
