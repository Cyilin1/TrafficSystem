#include "Verhalten.h"
#include "Fahrzeug.h"

double Verhalten::dStrecke(Fahrzeug &fahrzeug, double dZeitIntervall) {
  double dMaxSpeed = fahrzeug.dGeschwindigkeit();

  double dMoeglicheStrecke = dMaxSpeed * dZeitIntervall;

  double dReststrecke = p_rWeg.getLaenge() - fahrzeug.dGesamtstrecke();
  // 实际行驶的距离为最小值（即不会超过剩余路径长度）
  p_dLetzteBerechneteStrecke = std::min(dMoeglicheStrecke, dReststrecke);
  double dCanRunDis = p_rWeg.getLaenge() - fahrzeug.dGesamtstrecke() -
                      p_dLetzteBerechneteStrecke;
  std::cout << "还可行驶的距离为" << dCanRunDis << std::endl;
  return p_dLetzteBerechneteStrecke;
}
