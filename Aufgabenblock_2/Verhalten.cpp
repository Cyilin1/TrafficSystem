#include "Verhalten.h"
#include "Fahrzeug.h"

// double Verhalten::dStrecke(Fahrzeug &fahrzeug, double dZeitIntervall) {
//   double dMaxSpeed = fahrzeug.getMaxSpeed();

//  double dMoeglicheStrecke = dMaxSpeed * dZeitIntervall;

//  double dReststrecke = p_rWeg.getLaenge() - fahrzeug.getTotalDistance();
//  // 实际行驶的距离为最小值（即不会超过剩余路径长度）
//  p_dLetzteBerechneteStrecke = std::min(dMoeglicheStrecke, dReststrecke);
//  double dCanRunDis = p_rWeg.getLaenge() - fahrzeug.getTotalDistance() -
//                      p_dLetzteBerechneteStrecke;
//  std::cout << "还可行驶的距离为" << dCanRunDis << std::endl;
//  return p_dLetzteBerechneteStrecke;
//}

double TravelBehavior::calculateDistance(Vehicle &vehicle,
                                         double timeInterval) {
  double dMaxSpeed = vehicle.getMaxSpeed();

  double dMoeglicheStrecke = dMaxSpeed * timeInterval;

  double dReststrecke = p_rWeg.getLaenge() - vehicle.getCurrentDistance();
  // 实际行驶的距离为最小值（即不会超过剩余路径长度）
  m_lastCalculatedDistance = std::min(dMoeglicheStrecke, dReststrecke);
  double dCanRunDis = p_rWeg.getLaenge() - vehicle.getTotalDistance() -
                      m_lastCalculatedDistance;
  std::cout << vehicle.getName() << "还可行驶的距离为" << dCanRunDis
            << std::endl;
  return m_lastCalculatedDistance;
}
