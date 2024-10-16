//
// Created by Cyilin on 24-10-9.
//

#ifndef FAHRZEUG_H
#define FAHRZEUG_H
#include "Simulationsobjekt.h"
#include "Verhalten.h"

#include <iostream>
#include <limits>
#include <string>
extern double d_GlobaleZeit;

class Fahrzeug : public Simulationsobjekt {
protected:
  double p_dMaxGeschwindigkeit;     // 最大速度
  double p_dGesamtstrecke;          // 总行驶距离
  double p_dGesamtZeit;             // 总行驶时间
  double p_dAbschnittStrecke = 0.0; // 当前路径上的行驶距离

  std::unique_ptr<Verhalten> p_pVerhalten; // 管理Verhalten的智能指针

public:
  Fahrzeug(const Fahrzeug &) = delete;
  Fahrzeug();
  explicit Fahrzeug(const std::string &name) : Simulationsobjekt(name) {};
  Fahrzeug(const std::string &name, double maxGeschwindigkeit);
  virtual ~Fahrzeug() {};

  static void vKopf();
  virtual void vAusgeben() const override;
  virtual void vAusgeben(std::ostream &os) const;
  virtual void vSimulieren() override;
  virtual double dGeschwindigkeit() const;
  virtual double
  dTanken(double dMenge = std::numeric_limits<double>::infinity()) {
    return 0.0;
  };

  bool operator<(const Fahrzeug &other) const {
    return this->p_dGesamtstrecke < other.p_dGesamtstrecke;
  }

  Fahrzeug &operator=(const Fahrzeug &other) {
    if (this != &other) {
      p_sName = other.p_sName;
      p_dMaxGeschwindigkeit = other.p_dMaxGeschwindigkeit;
      // 不复制 p_iD，因为 ID 必须是唯一的
      // 不复制 p_dGesamtstrecke 和 p_dGesamtZeit,
      // 因为这些是特定于当前对象的状态
    }
    return *this;
  }

  // 为车辆设置新路径，创建新的 Verhalten 实例
  void vNeueStrecke(Weg &weg, bool parken = false, double startzeit = 0.0) {
    if (parken) {
      // 如果指定停车，则创建一个 Parken 实例，并传入开始时间
      p_pVerhalten = std::make_unique<Verhalten>(weg);
    } else {
      // 否则创建一个 Fahren 实例
      p_pVerhalten = std::make_unique<Verhalten>(weg);
    }
    p_dAbschnittStrecke = 0.0; // 进入新路径时重置当前路径行驶距离
  }

  double dGesamtstrecke() const { return p_dGesamtstrecke; }
};

#endif // FAHRZEUG_H
