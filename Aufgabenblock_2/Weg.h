#ifndef WEG_H
#define WEG_H

#include "Simulationsobjekt.h" // 只在这里前向声明 Fahrzeug 类
#include <iostream>
#include <limits> // For std::numeric_limits
#include <list>
#include <memory> // For smart pointers

class Fahrzeug;

enum class Tempolimit {
  Innerorts = 50,
  Landstrasse = 100,
  Autobahn = std::numeric_limits<int>::max()
};

class Weg : public Simulationsobjekt {
private:
  double p_dLaenge;                                  // 路径长度
  Tempolimit p_eTempolimit;                          // 速度限制
  std::list<std::unique_ptr<Fahrzeug>> p_pFahrzeuge; // 车辆列表

public:
  Weg();

  // 带名称、长度和可选速度限制的构造函数
  Weg(const std::string &name, double laenge,
      Tempolimit tempolimit = Tempolimit::Autobahn);

  void vAnnahme(std::unique_ptr<Fahrzeug> pFzg);
  // 模拟方法
  virtual void vSimulieren() override;

  // 输出方法
  static void vKopf();
  virtual void vAusgeben(std::ostream &os) const;
  virtual void vAusgeben() const override;

  // ==========================GETTER=======================
  double getTempolimit() const { return static_cast<double>(p_eTempolimit); }
  double getLaenge() const { return p_dLaenge; }
  const std::list<std::unique_ptr<Fahrzeug>> &getFahrzeuge() const {
    return p_pFahrzeuge;
  }
};

#endif // WEG_H
