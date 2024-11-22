#ifndef WEG_H
#define WEG_H

#include "Simulationsobject.h"
#include "vertagt_liste.h"
#include <iostream>
#include <limits> // For std::numeric_limits
#include <list>
#include <memory> // For smart pointers

class Vehicle;

enum class SpeedRestriction {
  Unlimited, // 无速度限制
  RuralRoad, // 乡村道路，限速 100 km/h
  UrbanArea  // 市区道路，限速 50 km/h
};

class Weg : public Simulationsobject {
private:
  double m_length;               // 路径长度
  SpeedRestriction m_speedLimit; // 速度限制
  deferred::DeferredList<std::unique_ptr<Vehicle>> m_vehicleList;
  //  std::list<std::unique_ptr<Vehicle>> p_pVehiclee; // 车辆列表

public:
  Weg();

  // 带名称、长度和可选速度限制的构造函数
  Weg(const std::string &name, double laenge,
      SpeedRestriction speedLimit = SpeedRestriction::Unlimited);

  void addVehicle(std::unique_ptr<Vehicle> pFzg);
  // 重载函数，接纳停放的车辆
  void addVehicle(std::unique_ptr<Vehicle> pVehicle, double dStartzeit);
  std::unique_ptr<Vehicle> removeVehicle(const Vehicle &Vehicle);
  // 模拟方法
  virtual void executeSimulation() override;

  // 输出方法
  static void displayHeader();
  virtual void displayData(std::ostream &os) const;
  virtual void displayData() const override;

  // ==========================GETTER=======================
  double getLaenge() const { return m_length; }
  double getTempolimit() const;
  const deferred::DeferredList<std::unique_ptr<Vehicle>> &getFahrzeuge() const {
    return m_vehicleList;
  }
};

#endif // WEG_H
