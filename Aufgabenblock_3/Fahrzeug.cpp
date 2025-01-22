//
// Created by Cyilin on 24-10-9.
//

#include "Fahrzeug.h"
#include "Fahren.h"
#include "Fahrzeugausnahme.h"
#include "Parken.h"

Fahrzeug::Fahrzeug() : Simulationsobjekt() {}

Fahrzeug::Fahrzeug(const std::string &name, double maxGeschwindigkeit)
    : Simulationsobjekt(name),
      p_dMaxGeschwindigkeit((maxGeschwindigkeit > 0) ? maxGeschwindigkeit
                                                     : 0), // 保证最大速度为正值
      p_dGesamtstrecke(0), p_dGesamtZeit(0) {}

void Fahrzeug::vAusgeben() const {
  Simulationsobjekt::vAusgeben();
  std::cout << std::resetiosflags(std::ios::adjustfield)
            << std::setiosflags(std::ios::left);
  // 设置输出列宽和精度，与表头的列宽一致
  std::cout << std::setw(10) << std::fixed << std::setprecision(2)
            << dGeschwindigkeit() << std::setw(10) << std::fixed
            << std::setprecision(2) << p_dGesamtstrecke;
}

void Fahrzeug::vAusgeben(std::ostream &os) const {
  Simulationsobjekt::vAusgeben();
  os << std::setw( 10 ) << std::fixed << std::setprecision( 2 ) << p_dMaxGeschwindigkeit << " | " << std::setw( 10 ) << std::fixed << std::setprecision( 2 ) << p_dGesamtstrecke << " | ";
}

void Fahrzeug::vEinlesen( std::istream& is ) {
  Simulationsobjekt::vEinlesen( is );  // Read p_sName firstly
  is >> p_dMaxGeschwindigkeit;
  if ( is.fail() ) {
      throw std::runtime_error( "Read p_sName failed!" );
  }
}

void Fahrzeug::vKopf() {
  Simulationsobjekt::vKopf();
  std::cout << std::setw(10) << "Max Speed" << " | " << std::setw(10)
            << "Mileage" << " | " << std::setw(10) << "Fuel" << std::setw(15)
            << "Current Speed" << std::endl;
  std::cout << "-------------------------------------------------------"
            << std::endl;
}

void Fahrzeug::vSimulieren() {
  if (p_pVerhalten) {
    //    double dAktuelleGeschwindigkeit = dGeschwindigkeit();
    double dZeitDelta = d_GlobaleZeit - p_dZeit;
    if (dZeitDelta <= 0)
      return;
    //    double dGefahreneStrecke = dAktuelleGeschwindigkeit * dZeitDelta;
    double dGefahreneStrecke = p_pVerhalten->dStrecke(*this, dZeitDelta);

    // 更新总行驶距离和总时间
    p_dAbschnittStrecke += dGefahreneStrecke; // 更新当前路径上的行驶距离
    p_dGesamtstrecke += dGefahreneStrecke;
    p_dGesamtZeit += dZeitDelta;
    p_dZeit = d_GlobaleZeit;

    //    // 检查是否需要抛出异常
    //    if (p_dAbschnittStrecke >= p_pVerhalten->getWeg().getLaenge()) {
    //      throw Streckenende(*this, p_pVerhalten->getWeg());
    //      //  抛出到达终点异常
    //    }
  }
}

void Fahrzeug::vNeueStrecke(Weg &weg) {
  p_pVerhalten = std::make_unique<Fahren>(weg); // 设置为行驶行为
  std::cout << "Fahrzeug " << getName() << " 被添加到路径 " << weg.getName()
            << " 上。\n";
  p_dAbschnittStrecke = 0.0; // 重置当前路径的行驶距离
}

void Fahrzeug::vNeueStrecke(Weg &weg, double dStartzeit) {
  p_pVerhalten = std::make_unique<Parken>(weg, dStartzeit); // 设置为停放行为
  p_dAbschnittStrecke = 0.0; // 重置当前路径的行驶距离
}

double Fahrzeug::dGeschwindigkeit() const { return p_dMaxGeschwindigkeit; }

void Fahrzeug::vLosfahren() {
  throw Losfahren(*this, p_pVerhalten->getWeg()); // 抛出启动异常
}
