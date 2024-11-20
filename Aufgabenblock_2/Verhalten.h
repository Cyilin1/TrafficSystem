#ifndef VERHALTEN_H
#define VERHALTEN_H

#include "Weg.h"

// class Verhalten {
// protected:
//   const Weg &p_rWeg;
//   double p_dLetzteBerechneteStrecke = 0.0; // 暂存每次仿真步骤中的计算结果

// public:
//   explicit Verhalten(const Weg &weg) : p_rWeg(weg) {}
//   virtual ~Verhalten() = default;

//  // 计算在给定时间间隔内的行驶距离
//  double dStrecke(Vehicle &Vehicle, double dZeitIntervall);

//  // 获取路径的引用
//  const Weg &getWeg() const { return p_rWeg; }
//};

class Verhalten {
public:
  explicit Verhalten(Weg &weg) : p_rWeg(weg) {}
  virtual ~Verhalten() {};

  // 纯虚函数，子类必须实现
  virtual double dStrecke(Vehicle &aFzg, double dZeitIntervall) = 0;
  // 获取路径的引用
  Weg &getWeg() const { return p_rWeg; }

protected:
  Weg &p_rWeg;                             // 路径引用
  double p_dLetzteBerechneteStrecke = 0.0; // 暂存每次仿真步骤中的计算结果
};

#endif // VERHALTEN_H
