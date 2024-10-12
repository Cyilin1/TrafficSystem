#include "pkw.h"

PKW::PKW(const std::string &name, double maxGeschwindigkeit, double verbrauch,
         double tankvolumen)
    : Fahrzeug(name, maxGeschwindigkeit), p_dVerbrauch(verbrauch),
      p_dTankvolumen(tankvolumen), p_dTankinhalt(tankvolumen / 2.0) {
  // 油箱中的油量初始化为油箱容量的一半
}

void PKW::vSimulieren() {
  double dZeitDelta = d_GlobaleZeit - p_dZeit;
  if (dZeitDelta <= 0)
    return;

  double dGefahreneStrecke = p_dMaxGeschwindigkeit * dZeitDelta;

  // 计算所需油量
  double dBenotigteMenge = (dGefahreneStrecke / 100.0) * p_dVerbrauch;

  // 如果油量不足，车辆只能行驶部分距离
  if (dBenotigteMenge > p_dTankinhalt) {
    dGefahreneStrecke = (p_dTankinhalt / p_dVerbrauch) * 100.0;
    p_dTankinhalt = 0; // 油量耗尽
  } else {
    p_dTankinhalt -= dBenotigteMenge;
  }

  // 更新总行驶距离和总行驶时间
  p_dGesamtstrecke += dGefahreneStrecke;
  p_dGesamtZeit += dZeitDelta;
  p_dZeit = d_GlobaleZeit;
}

void PKW::vAusgeben() const {
  Fahrzeug::vAusgeben();
  std::cout << std::setw(10) << p_dTankinhalt << std::setw(15)
            << dGeschwindigkeit();
}

void PKW::vAusgeben(std::ostream &os) const {
  Fahrzeug::vAusgeben(os);
  os << std::setw(10) << p_dTankinhalt << std::setw(15) << dGeschwindigkeit();
}

double PKW::dTanken(double dMenge) {
  if (dMenge == std::numeric_limits<double>::infinity()) {
    dMenge = p_dTankvolumen - p_dTankinhalt;
  }

  double tatsaechlicheMenge = std::min(dMenge, p_dTankvolumen - p_dTankinhalt);
  p_dTankinhalt += tatsaechlicheMenge;

  // 返回实际加的油量
  return tatsaechlicheMenge;
}

double PKW::dGeschwindigkeit() const { return p_dMaxGeschwindigkeit; }
