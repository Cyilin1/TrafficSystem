#ifndef Simulationsobject_H
#define Simulationsobject_H

#include <cmath>
#include <iomanip> // 用于格式化输出
#include <iostream>
#include <limits>
#include <string>

class Simulationsobject {
private:
  static int p_iMaxID; // 静态变量确保ID唯一
  const int p_iID;     // 每个对象的唯一ID

protected:
  std::string p_sName; // 名称
  double p_dZeit;      // 本地时间

public:
  // 禁止拷贝构造函数和赋值运算符
  Simulationsobject(const Simulationsobject &) = delete;
  Simulationsobject &operator=(const Simulationsobject &) = delete;

  Simulationsobject() : p_iID(++p_iMaxID), p_sName("") {};
  explicit Simulationsobject(const std::string &name)
      : p_iID(++p_iMaxID), p_sName(name), p_dZeit(0.0) {
    std::cout << "Simulationsobject created: Name=\"" << p_sName
              << "\", ID=" << p_iID << std::endl;
  }

  virtual ~Simulationsobject() {
    std::cout << "Simulationsobject destroyed: Name=\"" << p_sName
              << "\", ID=" << p_iID << std::endl;
  }

  // 纯虚函数
  virtual void executeSimulation() = 0;

  // 输出函数
  virtual void displayData() const;
  static void displayHeader();

  // 通过ID比较相等性
  bool operator==(const Simulationsobject &other) const {
    return this->p_iID == other.p_iID;
  }

  // 获取ID
  int getID() const { return p_iID; }

  // 获取名称
  const std::string &getName() const { return p_sName; }

  // 获取时间
  double getTime() const { return p_dZeit; }

  void setTime(double zeit) { p_dZeit = zeit; }
};
#endif // Simulationsobject_H
