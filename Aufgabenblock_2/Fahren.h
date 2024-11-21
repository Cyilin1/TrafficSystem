#ifndef FAHREN_H
#define FAHREN_H

#include "Verhalten.h"
class Vehicle;

class DrivingBehavior : public TravelBehavior {
public:
  DrivingBehavior(Weg &weg) : TravelBehavior(weg) {}

  // 行驶时计算行驶的距离
  double calculateDistance(Vehicle &vehicle, double timeInterval) override;
};

#endif // FAHREN_H
