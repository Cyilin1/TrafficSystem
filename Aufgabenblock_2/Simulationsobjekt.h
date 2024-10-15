#ifndef SIMULATIONSOBJEKT_H
#define SIMULATIONSOBJEKT_H

#include <cmath>
#include <iostream>
#include <limits>
#include <string>

class Simulationsobjekt {
private:
  static int p_iMaxID; // 静态变量确保ID唯一
  const int p_iID;     // 每个对象的唯一ID

protected:
  std::string p_sName; // 名称
  double p_dZeit;      // 本地时间

public:
  // 禁止拷贝构造函数和赋值运算符
  Simulationsobjekt(const Simulationsobjekt &) = delete;
  Simulationsobjekt &operator=(const Simulationsobjekt &) = delete;

  // 构造函数初始化ID和名称
  explicit Simulationsobjekt(const std::string &name)
      : p_iID(++p_iMaxID), p_sName(name), p_dZeit(0.0) {
    std::cout << "Simulationsobjekt created: Name=\"" << p_sName
              << "\", ID=" << p_iID << std::endl;
  }

  virtual ~Simulationsobjekt() {
    std::cout << "Simulationsobjekt destroyed: Name=\"" << p_sName
              << "\", ID=" << p_iID << std::endl;
  }

  // 纯虚函数
  virtual void vSimulieren() = 0;

  // 输出函数
  virtual void vAusgeben() const {
    std::cout << "Simulationsobjekt: " << p_sName << ", ID: " << p_iID
              << std::endl;
  }

  // 重载输出运算符
  friend std::ostream &operator<<(std::ostream &os,
                                  const Simulationsobjekt &obj) {
    obj.vAusgeben(os);
    return os;
  }

  // 通过ID比较相等性
  bool operator==(const Simulationsobjekt &other) const {
    return this->p_iID == other.p_iID;
  }

  // 获取ID
  int getID() const { return p_iID; }

  // 获取名称
  const std::string &getName() const { return p_sName; }

  // 获取时间
  double getZeit() const { return p_dZeit; }
};
#endif // SIMULATIONSOBJEKT_H
