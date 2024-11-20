//
// Created by Cyilin on 24-10-9.
//

#ifndef Vehicle_H
#define Vehicle_H
#include "Simulationsobjekt.h"
#include "Verhalten.h"

#include <iostream>
#include <limits>
#include <string>
extern double d_GlobaleZeit;

class Vehicle : public Simulationsobjekt {
protected:
  double m_maxSpeed;           // 最大速度
  double m_totalDistance;      // 总行驶距离
  double m_runingTime;         // 总行驶时间
  double m_currDistance = 0.0; // 当前路径上的行驶距离

  std::unique_ptr<Verhalten> m_behavior; // 管理Verhalten的智能指针

public:
  Vehicle(const Vehicle &) = delete;
  Vehicle();
  explicit Vehicle(const std::string &name) : Simulationsobjekt(name) {};
  Vehicle(const std::string &name, double maxSpeed);
  virtual ~Vehicle() {};

  static void vKopf();
  virtual void vAusgeben() const override;
  virtual void vAusgeben(std::ostream &os) const;
  virtual void vSimulieren() override;
  virtual double dGeschwindigkeit() const;
  virtual double
  dTanken(double dMenge = std::numeric_limits<double>::infinity()) {
    return 0.0;
  };
  virtual void vZeichnen(const Weg &weg) const { return; };

  bool operator<(const Vehicle &other) const {
    return this->m_totalDistance < other.m_totalDistance;
  }

  Vehicle &operator=(const Vehicle &other) {
    if (this != &other) {
      p_sName = other.p_sName;
      m_maxSpeed = other.m_maxSpeed;
      // 不复制 p_iD，因为 ID 必须是唯一的
      // 不复制 p_dGesamtstrecke 和 p_dGesamtZeit,
      // 因为这些是特定于当前对象的状态
    }
    return *this;
  }

  void vLosfahren();

  void vNeueStrecke(Weg &weg);

  // 重载 vNeueStrecke 函数，处理停放车辆（有开始时间）
  void vNeueStrecke(Weg &weg, double dStartzeit);
  double getAbschnittStrecke() const { return m_currDistance; }
  double dGesamtstrecke() const { return m_totalDistance; }
};

#endif // Vehicle_H
