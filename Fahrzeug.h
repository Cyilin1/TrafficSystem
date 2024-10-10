//
// Created by Cyilin on 24-10-9.
//

#ifndef FAHRZEUG_H
#define FAHRZEUG_H
#include <iomanip> // 用于格式化输出
#include <iostream>
#include <string>

class Fahrzeug {
private:
  std::string p_sName;          // 车辆名称
  const int p_iD;               // 车辆的唯一ID
  static int p_iMaxID;          // 静态变量，确保每个车辆的ID唯一
  double p_dMaxGeschwindigkeit; // 最大速度
  double p_dGesamtstrecke;      // 总行驶距离
  double p_dGesamtZeit;         // 总行驶时间
  double p_dZeit;               // 最近一次模拟的时间
public:
  // 默认构造函数，初始化名称为空字符串，ID自增
  //  Fahrzeug()
  //      : p_sName(""), p_iD(++p_iMaxID), p_dMaxGeschwindigkeit(0),
  //        p_dGesamtstrecke(0), p_dGesamtZeit(0), p_dZeit(0) {
  //    std::cout << "Fahrzeug created: Name=\"" << p_sName << "\", ID=" << p_iD
  //              << std::endl;
  //  }
  Fahrzeug() : p_sName(""), p_iD(++p_iMaxID) {
    std::cout << "Fahrzeug created: Name=\"" << p_sName << "\", ID=" << p_iD
              << std::endl;
  }

  // 带名称参数的构造函数
  explicit Fahrzeug(const std::string &name) : p_sName(name), p_iD(++p_iMaxID) {
    std::cout << "Fahrzeug created: Name=\"" << p_sName << "\", ID=" << p_iD
              << std::endl;
  }
  // 带名称和最大速度的构造函数
  //  Fahrzeug(const std::string &name, double maxGeschwindigkeit)
  //      : p_sName(name), p_iD(++p_iMaxID),
  //        p_dMaxGeschwindigkeit((maxGeschwindigkeit > 0)
  //                                  ? maxGeschwindigkeit
  //                                  : 0), // 保证最大速度为正值
  //        p_dGesamtstrecke(0), p_dGesamtZeit(0), p_dZeit(0) {
  //    std::cout << "Fahrzeug [" << p_sName << "] with ID: " << p_iD
  //              << " created, Max Speed: " << p_dMaxGeschwindigkeit << "
  //              km/h.\n";
  //  }

  // 析构函数
  ~Fahrzeug() {
    std::cout << "Fahrzeug destroyed: Name=\"" << p_sName << "\", ID=" << p_iD
              << std::endl;
  }

  // 输出表头函数
  static void vKopf() {
    std::cout << std::left << std::setw(5) << "ID" << std::setw(10) << "名称"
              << std::setw(15) << "最大速度" << std::setw(10) << "总里程数"
              << std::endl;
    std::cout << "--------------------------------------" << std::endl;
  }

  // 输出车辆数据的函数
  void vAusgeben() const {
    std::cout << std::left << std::setw(5) << p_iD << std::setw(10) << p_sName
              << std::setw(15) << std::fixed << std::setprecision(2)
              << p_dMaxGeschwindigkeit << std::setw(10) << std::fixed
              << std::setprecision(2) << p_dGesamtstrecke;
  }

  // 返回车辆名称（常量成员函数）
  const std::string &getName() const { return p_sName; }

  // 返回车辆ID（常量成员函数）
  int getID() const { return p_iD; }
};

// 静态变量初始化

#endif // FAHRZEUG_H
