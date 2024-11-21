#include "Parken.h"
#include "Fahren.h"
#include "Fahrzeug.h"
#include "Fahrzeugausnahme.h"

double ParkingBehavior::calculateDistance(Vehicle &vehicle,
                                          double dZeitIntervall) {
  if (d_GlobaleZeit < p_dStartzeit) {
    std::cout << "Fahrzeug " << vehicle.getName() << " 停放中，启动时间未到达。"
              << std::endl;
    return 0.0;
  }

  if (!bGestartet) {
    std::cout << "Fahrzeug " << vehicle.getName() << " 启动了，开始行驶。"
              << std::endl;
    bGestartet = true;
    vehicle.setTime(d_GlobaleZeit);
    throw StartException(vehicle, TravelBehavior::getWeg());
  }

  return TravelBehavior::calculateDistance(vehicle, dZeitIntervall);
}
