#include "pkw.h"
#include "Fahrzeugausnahme.h"
#include "SimuClient.h"

PKW::PKW(const std::string &name, double maxGeschwindigkeit, double verbrauch,
         double tankvolumen)
    : Fahrzeug(name, maxGeschwindigkeit), p_dVerbrauch(verbrauch),
      p_dTankvolumen(tankvolumen), p_dTankinhalt(tankvolumen / 2.0) {
  // 油箱中的油量初始化为油箱容量的一半
}

void PKW::vSimulieren() {
  if (!p_pVerhalten)
    return;
  double dZeitDelta = d_GlobaleZeit - p_dZeit;
  if (dZeitDelta <= 0)
    return;
  double dGefahreneStrecke = p_pVerhalten->dStrecke(*this, dZeitDelta);
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
  p_dAbschnittStrecke += dGefahreneStrecke;
  p_dGesamtstrecke += dGefahreneStrecke;
  p_dGesamtZeit += dZeitDelta;
  p_dZeit = d_GlobaleZeit;
  // 检查是否需要抛出异常
  if (p_dAbschnittStrecke >= p_pVerhalten->getWeg().getLaenge()) {
    throw Streckenende(*this, p_pVerhalten->getWeg());
    //  抛出到达终点异常
  }
}

void PKW::vEinlesen( std::istream& is ) {
  Fahrzeug::vEinlesen( is );
  is >> p_dVerbrauch >> p_dTankvolumen;
  if ( is.fail() ) {
    throw std::runtime_error( "Read p_dVerbrauch/p_dTankvolumen failed!" );
  }
}

void PKW::vAusgeben() const {
  Fahrzeug::vAusgeben();
  std::cout << std::setw( 10 ) << p_dTankinhalt << std::setw( 15 ) << this->dGeschwindigkeit();
}

void PKW::vAusgeben(std::ostream &os) const {
  Fahrzeug::vAusgeben(os);
  os << std::setw( 10 ) << p_dTankinhalt << std::setw( 15 ) << this->dGeschwindigkeit();
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

void PKW::vZeichnen(const Weg &weg) const {
  double relPosition = p_dAbschnittStrecke / weg.getLaenge();      // 计算相对位置
  double kmH = this->dGeschwindigkeit();                   // 获取车辆速度
  double tank = p_dTankinhalt;                             // 获取油箱剩余量
  bZeichnePKW(this->getName(), weg.getName(), relPosition, kmH, tank);
}

double PKW::dGeschwindigkeit() const {
  double maxGeschwindigkeit = p_dMaxGeschwindigkeit;
  if (p_pVerhalten) {
    double wegTempolimit = p_pVerhalten->getWeg().dGetTempolimit();
    //    if ( maxGeschwindigkeit > wegTempolimit ) {
    //        std::cout << "超过限速，进行降速操作！！" << std::endl;
    //    }
    return std::min(maxGeschwindigkeit, wegTempolimit); // 取最小值
  }
  return maxGeschwindigkeit;
}
