#include "Simulationsobjekt.h"

void Simulationsobjekt::vKopf() {
  std::cout << std::resetiosflags(std::ios::adjustfield)
            << std::setiosflags(std::ios::left);
  std::cout << std::setw(5) << "ID" << " | " << std::setw(15) << "Name"
            << " | ";
}

void Simulationsobjekt::vEinlesen( std::istream& is ) {
  if ( !p_sName.empty() ) {
      throw std::runtime_error( "The Object is initaized!" );
  }
  is >> p_sName;
  if ( is.fail() ) {
      throw std::runtime_error( "Read p_sName failed!" );
  }
}

void Simulationsobjekt::vAusgeben() const {
  std::cout << std::resetiosflags(std::ios::adjustfield)
            << std::setiosflags(std::ios::left);
  std::cout << std::setw(5) << p_iID << " | " << std::setw(15) << p_sName
            << " | ";
}
