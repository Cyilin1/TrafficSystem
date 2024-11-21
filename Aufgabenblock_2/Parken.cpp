#include "Parken.h"
#include "Fahren.h"
#include "Fahrzeug.h"
#include "Fahrzeugausnahme.h"

double Parken::dStrecke(Vehicle &aFzg, double dZeitIntervall) {
  if (d_GlobaleZeit < p_dStartzeit) {
    std::cout << "Fahrzeug " << aFzg.getName() << " 停放中，启动时间未到达。"
              << std::endl;
    return 0.0;
  }

  if (!bGestartet) {
    std::cout << "Fahrzeug " << aFzg.getName() << " 启动了，开始行驶。"
              << std::endl;
    bGestartet = true;
    aFzg.setZeit(d_GlobaleZeit);
    throw StartException(aFzg, Verhalten::getWeg());
  }

  return Verhalten::dStrecke(aFzg, dZeitIntervall);
}
