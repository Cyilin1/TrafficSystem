#include "Fahrzeugausnahme.h"
#include "Fahrzeug.h"

Fahrzeugausnahme::Fahrzeugausnahme(Fahrzeug &fzg, const Weg &weg)
    : p_Fahrzeug(fzg), p_Weg(weg) {}

void Losfahren::vBearbeiten() const {
  std::cout << "Warning ：车辆 " << p_Fahrzeug.getName() << " 在路径 "
            << p_Weg.getName() << " 上启动了。" << std::endl;
}

void Streckenende::vBearbeiten() const {
  std::cout << "Warning ：车辆 " << p_Fahrzeug.getName() << " 到达了路径 "
            << p_Weg.getName() << " 的终点。" << std::endl;
}
