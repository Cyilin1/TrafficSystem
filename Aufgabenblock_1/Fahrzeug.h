//
// Created by Cyilin on 24-10-9.
//

#ifndef FAHRZEUG_H
#define FAHRZEUG_H
#include <iomanip> // 用于格式化输出
#include <iostream>
#include <limits>
#include <string>
extern double d_GlobaleZeit;

class Fahrzeug {

private:
  static int p_iMaxID; // 静态变量，确保每个车辆的ID唯一
  const int p_iD;      // 车辆的唯一ID

protected:
  std::string p_sName;          // 车辆名称
  double p_dMaxGeschwindigkeit; // 最大速度
  double p_dGesamtstrecke;      // 总行驶距离
  double p_dGesamtZeit;         // 总行驶时间
  double p_dZeit;               // 最近一次模拟的时间

public:
  Fahrzeug(const Fahrzeug &) = delete;
  Fahrzeug();
  explicit Fahrzeug(const std::string &name) : p_sName(name), p_iD(++p_iMaxID) {
    std::cout << "Fahrzeug created: Name=\"" << p_sName << "\", ID=" << p_iD
              << std::endl;
  }
  Fahrzeug(const std::string &name, double maxGeschwindigkeit);
  virtual ~Fahrzeug();

  static void vKopf();

  virtual void vAusgeben() const;
  virtual void vAusgeben(std::ostream &os) const;
  virtual void vSimulieren();
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

  const std::string &getName() const { return p_sName; }

  int getID() const { return p_iD; }
};

#endif // FAHRZEUG_H
