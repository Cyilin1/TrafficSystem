#include "Fahren.h"
#include "Fahrzeug.h"
#include "Fahrzeugausnahme.h"

double DrivingBehavior::calculateDistance(Vehicle &vehicle,
                                          double timeInterval) {
  double dMaxSpeed = vehicle.getMaxSpeed();

  double dMoeglicheStrecke = dMaxSpeed * timeInterval;
  if (vehicle.getCurrentDistance() + dMoeglicheStrecke >= p_rWeg.getLaenge()) {
    dMoeglicheStrecke = p_rWeg.getLaenge() - vehicle.getCurrentDistance();
    //    throw Streckenende(fahrzeug, p_rWeg);
  }

  double dCanRunDis =
      p_rWeg.getLaenge() - vehicle.getCurrentDistance() - dMoeglicheStrecke;
  std::cout << vehicle.getName() << " 还可行驶的距离为" << dCanRunDis
            << std::endl;
  return dMoeglicheStrecke;
}
