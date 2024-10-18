#include "Parken.h"
#include "Fahrzeug.h"

double Parken::dStrecke(Fahrzeug &aFzg, double dZeitIntervall) {
  if (d_GlobaleZeit <= p_dStartzeit) {
    std::cout << "Fahrzeug " << aFzg.getName() << " 停放中，启动时间未到达。"
              << std::endl;
    return 0.0;
  } else {
    std::cout << "Fahrzeug " << aFzg.getName() << " 启动了，开始行驶。"
              << std::endl;
    return Verhalten::dStrecke(aFzg, dZeitIntervall);
  }
}
