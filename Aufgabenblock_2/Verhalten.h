#ifndef VERHALTEN_H
#define VERHALTEN_H

#include "Weg.h"

class Verhalten {
protected:
  const Weg &p_rWeg;
  double p_dLetzteBerechneteStrecke = 0.0; // 暂存每次仿真步骤中的计算结果

public:
  explicit Verhalten(const Weg &weg) : p_rWeg(weg) {}
  virtual ~Verhalten() = default;

  // 虚函数，返回当前行为下的最大速度
  //  double dGeschwindigkeit(const Fahrzeug &fahrzeug) const;
  // 计算在给定时间间隔内的行驶距离
  double dStrecke(Fahrzeug &fahrzeug, double dZeitIntervall);

  // 获取路径的引用
  const Weg &getWeg() const { return p_rWeg; }
};

#endif // VERHALTEN_H
