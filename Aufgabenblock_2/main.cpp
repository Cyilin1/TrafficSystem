#include "Simulationsobjekt.h"

#include "Weg.h"
#include "fahrrad.h"
#include "pkw.h"
#include <iostream>
#include <string>
#include <vector>

double d_GlobaleZeit = 0.0; // 定义全局时钟
const double epsilon = 1e-6;
const double refuelInterval = 3.0;

int Simulationsobjekt::p_iMaxID = 0;

std::ostream &operator<<(std::ostream &os, const Fahrzeug &fahrzeug) {
  fahrzeug.vAusgeben(os);
  return os;
}

std::ostream &operator<<(std::ostream &os, const Weg &fahrzeug) {
  fahrzeug.vAusgeben(os);
  return os;
}

void vAufgabe_1_1() {
  // 创建一些 Fahrzeug 对象
  Fahrzeug fahrzeug1("PKW1", 40.00);
  Fahrzeug fahrzeug2("AUTO3", 30.00);

  // 输出表头
  Fahrzeug::vKopf();

  // 输出车辆数据
  fahrzeug1.vAusgeben();
  std::cout << std::endl; // 主函数负责换行
  fahrzeug2.vAusgeben();
  std::cout << std::endl; // 主函数负责换行  Aufgabe_1();
  // 模拟时间推进
  d_GlobaleZeit = 2.0; // 2小时
  fahrzeug1.vSimulieren();
  fahrzeug2.vSimulieren();

  // 第二次输出车辆数据，应该看到车辆的总里程数变化
  fahrzeug1.vAusgeben();
  std::cout << std::endl;
  fahrzeug2.vAusgeben();
  std::cout << std::endl;

  d_GlobaleZeit = 5.0; // 5小时
  fahrzeug1.vSimulieren();
  fahrzeug2.vSimulieren();

  // 输出最终车辆数据
  fahrzeug1.vAusgeben();
  std::cout << std::endl;
  fahrzeug2.vAusgeben();
  std::cout << std::endl;
}

void vAufgabe_1a0() {
  std::vector<std::unique_ptr<Fahrzeug>> fahrzeuge;

  fahrzeuge.push_back(std::make_unique<Fahrzeug>("Benz", 100));
  fahrzeuge.push_back(std::make_unique<Fahrzeug>("BMW", 80));
  fahrzeuge.push_back(std::make_unique<Fahrzeug>("Audi", 60));

  // 输出表头
  Fahrzeug::vKopf();

  // 模拟一段时间，假设总模拟时间为10小时，每次递增0.5小时
  const double zeitschritt = 0.5; // 每次增加0.5小时
  const double simzeit = 10.0;    // 总模拟时间为10小时

  while (d_GlobaleZeit <= simzeit) {
    // 调用每个车辆的模拟函数
    for (auto &fahrzeug : fahrzeuge) {
      fahrzeug->vSimulieren();
    }

    // 输出每个时间步的车辆状态
    for (const auto &fahrzeug : fahrzeuge) {
      fahrzeug->vAusgeben();
      std::cout << std::endl; // 控制换行
    }

    // 输出当前时间（用于跟踪时间进度）
    std::cout << "当前时间: " << std::fixed << std::setprecision(2)
              << d_GlobaleZeit << " 小时" << std::endl;
    std::cout << "--------------------------------------" << std::endl;
    // 增加全局时钟
    d_GlobaleZeit += zeitschritt;
  }
}

void vAufgabe_2() {
  int pkwCount, fahrradCount;

  std::cout << "请输入要生成的汽车数量: ";
  std::cin >> pkwCount;
  std::cout << "请输入要生成的自行车数量: ";
  std::cin >> fahrradCount;

  std::vector<std::unique_ptr<Fahrzeug>> fahrzeuge;

  for (int i = 0; i < pkwCount; ++i) {
    std::string name;
    double maxGeschwindigkeit, verbrauch, tankvolumen;

    std::cout << "请输入第 " << (i + 1) << " 辆汽车的名称: ";
    std::cin >> name;
    std::cout << "请输入最大速度(km/h): ";
    std::cin >> maxGeschwindigkeit;
    std::cout << "请输入每百公里的油耗(升): ";
    std::cin >> verbrauch;
    std::cout << "请输入油箱容量(升) (可选，默认 55 升): ";
    std::cin >> tankvolumen;

    // 创建 PKW 对象并放入 vector
    fahrzeuge.push_back(std::make_unique<PKW>(name, maxGeschwindigkeit,
                                              verbrauch, tankvolumen));
  }

  for (int i = 0; i < fahrradCount; ++i) {
    std::string name;
    double maxGeschwindigkeit;

    std::cout << "请输入第 " << (i + 1) << " 辆自行车的名称: ";
    std::cin >> name;
    std::cout << "请输入最大速度(km/h): ";
    std::cin >> maxGeschwindigkeit;

    // 创建 Fahrrad 对象并放入 vector
    fahrzeuge.push_back(std::make_unique<Fahrrad>(name, maxGeschwindigkeit));
  }

  std::cout << "\n已生成的车辆信息:\n";
  Fahrzeug::vKopf();
  for (const auto &fahrzeug : fahrzeuge) {
    //    fahrzeug->vAusgeben();
    //    std::cout << std::endl;
    std::cout << *fahrzeug;
    std::cout << std::endl;
  }

  double simTimeStep = 0.5;         // 每个时间步增加0.5小时
  double totalSimulationTime = 8.0; // 总模拟时间5小时
  double lastRefuelTime = 0.0;      // 上次加油的时间

  while (d_GlobaleZeit < totalSimulationTime) {
    // 增加全局时间
    d_GlobaleZeit += simTimeStep;

    // 模拟每个车辆的状态
    for (auto &fahrzeug : fahrzeuge) {
      fahrzeug->vSimulieren();
    }

    // 输出车辆的当前状态
    Fahrzeug::vKopf();
    for (auto &fahrzeug : fahrzeuge) {
      std::cout << *fahrzeug;
      std::cout << std::endl;
    }

    if (std::fabs(d_GlobaleZeit - lastRefuelTime - refuelInterval) < epsilon ||
        d_GlobaleZeit > lastRefuelTime + refuelInterval) {
      std::cout << "\n达到 " << lastRefuelTime + refuelInterval
                << " 小时，为所有汽车加满油。\n";
      for (auto &fahrzeug : fahrzeuge) {
        // 尝试加油
        PKW *pkw = dynamic_cast<PKW *>(fahrzeug.get());
        if (pkw) {
          double fuelAdded = pkw->dTanken();
          std::cout << pkw->getName() << " 加油: " << fuelAdded << " 升\n";
        }
      }
      lastRefuelTime += refuelInterval;
    }

    std::cout << "当前时间: " << std::fixed << std::setprecision(2)
              << d_GlobaleZeit << " 小时" << std::endl;
    std::cout << "--------------------------------------------" << std::endl;
    std::cout << std::endl;
  }
  // 使用 operator< 进行比较
  if (fahrzeuge[0] < fahrzeuge[1]) {
    std::cout << fahrzeuge[0]->getName() << " 的行驶距离小于 "
              << fahrzeuge[1]->getName() << "\n";
  } else {
    std::cout << fahrzeuge[0]->getName() << " 的行驶距离大于或等于 "
              << fahrzeuge[1]->getName() << "\n";
  }
}

void vAufgabe_3() {
  Fahrzeug fz1("Auto 1", 120.0);
  Fahrzeug fz2("Auto 2", 150.0);

  std::cout << "初始状态:" << std::endl;
  Fahrzeug::vKopf();
  std::cout << fz1 << std::endl;
  std::cout << fz2 << std::endl;

  fz1 = fz2; // 将 fz2 赋值给 fz1

  std::cout << "\n赋值后的状态:" << std::endl;
  Fahrzeug::vKopf();
  std::cout << fz1 << std::endl;
  std::cout << fz2 << std::endl;

  double simTimeStep = 0.5;         // 每个时间步增加0.5小时
  double totalSimulationTime = 8.0; // 总模拟时间5小时

  while (d_GlobaleZeit < totalSimulationTime) {
    d_GlobaleZeit += simTimeStep;
    fz1.vSimulieren();
    fz2.vSimulieren();

    Fahrzeug::vKopf();
    std::cout << fz1 << std::endl;
    std::cout << fz2 << std::endl;

    std::cout << "当前时间: " << std::fixed << std::setprecision(2)
              << d_GlobaleZeit << " 小时" << std::endl;
    std::cout << "--------------------------------------------" << std::endl;
    std::cout << std::endl;
  }
}

void vAufgabe_4() {
  // 创建一个 Weg 对象，名称为"Autobahn"，长度为100，默认速度限制为无限制
  Weg autobahn("Autobahn", 100.0, Tempolimit::Autobahn);

  // 创建两个车辆，并添加到Weg中
  autobahn.addFahrzeug(std::make_unique<Fahrzeug>("BMW", 120.0));
  autobahn.addFahrzeug(std::make_unique<Fahrzeug>("Audi", 130.0));

  Weg::vKopf();
  std::cout << autobahn << std::endl;
}

int main() {
  vAufgabe_4();
  std::cout << "\n=== 程序结束 ===" << std::endl;
  return 0;
}
