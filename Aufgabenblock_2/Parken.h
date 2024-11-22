#ifndef PARKEN_H
#define PARKEN_H

#include "Verhalten.h"

class ParkingBehavior : public TravelBehavior {
public:
  ParkingBehavior(Weg &weg, double startTime)
      : TravelBehavior(weg), m_startTime(startTime) {}

  // 停放车辆，在达到启动时间之前返回 0.0
  double calculateDistance(Vehicle &vehicle, double timeInterval) override;

private:
  double m_startTime;      // 停放开始时间
  bool bGestartet = false; // 记录是否已经启动
};

#endif // PARKEN_H
