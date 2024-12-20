#ifndef WEG_H
#define WEG_H

#include "Simulationsobjekt.h"
#include "vertagt_liste.h"
#include <iostream>
#include <limits> // For std::numeric_limits
#include <list>
#include <memory> // For smart pointers

class Fahrzeug;

enum class Tempolimit {
  Unlimited,   // 无速度限制
  Landstrasse, // 乡村道路，限速 100 km/h
  Innerorts    // 市区道路，限速 50 km/h
};

class Weg : public Simulationsobjekt {
private:
  double p_dLaenge;         // 路径长度
  Tempolimit p_eTempolimit; // 速度限制
  vertagt::VListe<std::unique_ptr<Fahrzeug>> p_pFahrzeuge;
  bool                                       bUeberholverbot;  // 超车禁令

  public:
  Weg();

  // 带名称、长度和可选速度限制的构造函数
  Weg( const std::string& name, double laenge, Tempolimit tempolimit = Tempolimit::Unlimited, bool ueberholverbot = false );

  void vAnnahme( std::unique_ptr< Fahrzeug > pFzg );
  // 重载函数，接纳停放的车辆
  void vAnnahme(std::unique_ptr<Fahrzeug> pFahrzeug, double dStartzeit);
  std::unique_ptr<Fahrzeug> pAbgabe(const Fahrzeug &fahrzeug);
  // 模拟方法
  virtual void vSimulieren() override;

  // 输出方法
  static void vKopf();
  virtual void vAusgeben(std::ostream &os) const;
  virtual void vAusgeben() const override;

  // 获取指定车辆虚拟障碍的位置
  double getBarriere( const Fahrzeug& faz );

  // ==========================GETTER=======================
  double getTempolimit() const { return static_cast<double>(p_eTempolimit); }
  double getLaenge() const {
      return p_dLaenge;
  }
  double getUeberholverbot() const {
      return bUeberholverbot;
  }
  double dGetTempolimit() const;

  const vertagt::VListe<std::unique_ptr<Fahrzeug>> &getFahrzeuge() const {
    return p_pFahrzeuge;
  }
};

#endif // WEG_H
