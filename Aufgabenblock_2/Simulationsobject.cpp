#include "Simulationsobject.h"

void Simulationsobject::displayHeader() {
  std::cout << std::resetiosflags(std::ios::adjustfield)
            << std::setiosflags(std::ios::left);
  std::cout << std::setw(5) << "ID" << " | " << std::setw(15) << "Name"
            << " | ";
}

void Simulationsobject::displayData() const {
  std::cout << std::resetiosflags(std::ios::adjustfield)
            << std::setiosflags(std::ios::left);
  std::cout << std::setw(5) << p_iID << " | " << std::setw(15) << p_sName
            << " | ";
}
