//
// Created by Cyilin on 24-10-9.
//

#ifndef Vehicle_H
#define Vehicle_H
#include "Simulationsobject.h"
#include "Verhalten.h"

#include <iostream>
#include <limits>
#include <string>
extern double d_GlobaleZeit;

class Vehicle : public Simulationsobject {
protected:
  double m_maxSpeed;           // 最大速度
  double m_totalDistance;      // 总行驶距离
  double m_runingTime;         // 总行驶时间
  double m_currDistance = 0.0; // 当前路径上的行驶距离

  std::unique_ptr<TravelBehavior> m_behavior; // 管理Verhalten的智能指针

public:
  Vehicle(const Vehicle &) = delete;
  Vehicle();
  explicit Vehicle(const std::string &name) : Simulationsobject(name) {};
  Vehicle(const std::string &name, double maxSpeed);
  virtual ~Vehicle() {};

  // ===============Output========================
  static void displayHeader();
  virtual void displayData() const override;
  virtual void displayData(std::ostream &os) const;
  virtual void executeSimulation() override;

  virtual double
  dTanken(double dMenge = std::numeric_limits<double>::infinity()) {
    return 0.0;
  };
  virtual void drawPath(const Weg &weg) const { return; };
  void setNewPath(Weg &weg);
  // 重载 setNewPath 函数，处理停放车辆（有开始时间）
  void setNewPath(Weg &weg, double dStartzeit);

  // ===========================Operator=======================
  bool operator<(const Vehicle &other) const {
    return this->m_totalDistance < other.m_totalDistance;
  }
  Vehicle &operator=(const Vehicle &other) {
    if (this != &other) {
      p_sName = other.p_sName;
      m_maxSpeed = other.m_maxSpeed;
      // 不复制 p_iD，因为 ID 必须是唯一的
      // 不复制 p_getTotalDistance 和 p_dGesamtZeit,
      // 因为这些是特定于当前对象的状态
    }
    return *this;
  }
  // void vLosfahren();

  // ============================Getter========================
  virtual double getMaxSpeed() const;
  double getCurrentDistance() const { return m_currDistance; }
  double getTotalDistance() const { return m_totalDistance; }
};

#endif // Vehicle_H
