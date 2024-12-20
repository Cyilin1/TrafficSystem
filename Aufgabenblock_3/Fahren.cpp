#include "Fahren.h"
#include "Fahrzeug.h"
#include "Fahrzeugausnahme.h"

double Fahren::dStrecke(Fahrzeug &fahrzeug, double dZeitIntervall) {
  double dMaxSpeed = fahrzeug.dGeschwindigkeit();

  double dMoeglicheStrecke = dMaxSpeed * dZeitIntervall;
  double dBarriere         = p_rWeg.getBarriere( fahrzeug );

  if ( fahrzeug.getAbschnittStrecke() + dMoeglicheStrecke >= dBarriere ) {
      dMoeglicheStrecke = dBarriere - fahrzeug.getAbschnittStrecke();
      //    throw Streckenende(fahrzeug, p_rWeg);
  }

  double dCanRunDis = dBarriere - fahrzeug.getAbschnittStrecke() - dMoeglicheStrecke;
  std::cout << fahrzeug.getName() << " 还可行驶的距离为" << dCanRunDis
            << std::endl;
  return dMoeglicheStrecke;
}

//
