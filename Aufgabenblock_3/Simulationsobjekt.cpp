#include "Simulationsobjekt.h"

void Simulationsobjekt::vKopf() {
  std::cout << std::resetiosflags(std::ios::adjustfield)
            << std::setiosflags(std::ios::left);
  std::cout << std::setw(5) << "ID" << " | " << std::setw(15) << "Name"
            << " | ";
}

void Simulationsobjekt::vAusgeben() const {
  std::cout << std::resetiosflags(std::ios::adjustfield)
            << std::setiosflags(std::ios::left);
  std::cout << std::setw(5) << p_iID << " | " << std::setw(15) << p_sName
            << " | ";
}
