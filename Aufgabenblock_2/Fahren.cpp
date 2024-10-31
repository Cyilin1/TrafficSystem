#include "Fahren.h"
#include "Fahrzeug.h"
#include "Fahrzeugausnahme.h"

double Fahren::dStrecke(Fahrzeug &fahrzeug, double dZeitIntervall) {
  double dMaxSpeed = fahrzeug.dGeschwindigkeit();

  double dMoeglicheStrecke = dMaxSpeed * dZeitIntervall;
  if (fahrzeug.getAbschnittStrecke() + dMoeglicheStrecke >=
      p_rWeg.getLaenge()) {
    dMoeglicheStrecke = p_rWeg.getLaenge() - fahrzeug.getAbschnittStrecke();
    //    throw Streckenende(fahrzeug, p_rWeg);
  }

  double dCanRunDis =
      p_rWeg.getLaenge() - fahrzeug.getAbschnittStrecke() - dMoeglicheStrecke;
  std::cout << fahrzeug.getName() << " 还可行驶的距离为" << dCanRunDis
            << std::endl;
  return dMoeglicheStrecke;
}
