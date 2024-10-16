#include "Simulationsobjekt.h"

void Simulationsobjekt::vKopf() {
  std::cout << std::resetiosflags(std::ios::adjustfield)
            << std::setiosflags(std::ios::left);
  std::cout << std::setw(5) << "ID" << std::setw(10) << "Name" << std::setw(10)
            << "Max Speed" << std::setw(10) << "Mileage" << std::setw(10)
            << "Fuel" << std::setw(15) << "Current Speed" << std::endl;
  std::cout << "-------------------------------------------------------"
            << std::endl;
}

void Simulationsobjekt::vAusgeben() const {
  std::cout << std::resetiosflags(std::ios::adjustfield)
            << std::setiosflags(std::ios::left);
  std::cout << std::setw(5) << p_iID << " | " << std::setw(15) << p_sName;
}
