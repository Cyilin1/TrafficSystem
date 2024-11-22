#include "SimuClient.h"
#include "Simulationsobject.h"
#include "Weg.h"
#include "fahrrad.h"
#include "pkw.h"
#include "vertagt_liste.h"
#include <iostream>
#include <random>
#include <string>
#include <vector>

double globalTime = 0.0; // 定义全局时钟
const double epsilon = 1e-6;
const double refuelInterval = 3.0;

int Simulationsobject::p_iMaxID = 0;

std::ostream &operator<<(std::ostream &os, const Vehicle &vehicle) {
  vehicle.displayData(os);
  return os;
}

std::ostream &operator<<(std::ostream &os, const Weg &fahrzeug) {
  fahrzeug.displayData(os);
  return os;
}

void vAufgabe_1_1() {
  // 创建一些 Fahrzeug 对象
  Vehicle fahrzeug1("PKW1", 40.00);
  Vehicle fahrzeug2("AUTO3", 30.00);

  // 输出表头
  Vehicle::displayHeader();

  // 输出车辆数据
  fahrzeug1.displayData();
  std::cout << std::endl; // 主函数负责换行
  fahrzeug2.displayData();
  std::cout << std::endl; // 主函数负责换行  Aufgabe_1();
  // 模拟时间推进
  globalTime = 2.0; // 2小时
  fahrzeug1.executeSimulation();
  fahrzeug2.executeSimulation();

  // 第二次输出车辆数据，应该看到车辆的总里程数变化
  fahrzeug1.displayData();
  std::cout << std::endl;
  fahrzeug2.displayData();
  std::cout << std::endl;

  globalTime = 5.0; // 5小时
  fahrzeug1.executeSimulation();
  fahrzeug2.executeSimulation();

  // 输出最终车辆数据
  fahrzeug1.displayData();
  std::cout << std::endl;
  fahrzeug2.displayData();
  std::cout << std::endl;
}

void vAufgabe_1a0() {
  std::vector<std::unique_ptr<Vehicle>> fahrzeuge;

  fahrzeuge.push_back(std::make_unique<Vehicle>("Benz", 100));
  fahrzeuge.push_back(std::make_unique<Vehicle>("BMW", 80));
  fahrzeuge.push_back(std::make_unique<Vehicle>("Audi", 60));

  // 输出表头
  Vehicle::displayHeader();

  // 模拟一段时间，假设总模拟时间为10小时，每次递增0.5小时
  const double zeitschritt = 0.5; // 每次增加0.5小时
  const double simzeit = 10.0;    // 总模拟时间为10小时

  while (globalTime <= simzeit) {
    // 调用每个车辆的模拟函数
    for (auto &fahrzeug : fahrzeuge) {
      fahrzeug->executeSimulation();
    }

    // 输出每个时间步的车辆状态
    for (const auto &fahrzeug : fahrzeuge) {
      fahrzeug->displayData();
      std::cout << std::endl; // 控制换行
    }

    // 输出当前时间（用于跟踪时间进度）
    std::cout << "当前时间: " << std::fixed << std::setprecision(2)
              << globalTime << " 小时" << std::endl;
    std::cout << "--------------------------------------" << std::endl;
    // 增加全局时钟
    globalTime += zeitschritt;
  }
}

void vAufgabe_2() {
  int pkwCount, fahrradCount;

  std::cout << "请输入要生成的汽车数量: ";
  std::cin >> pkwCount;
  std::cout << "请输入要生成的自行车数量: ";
  std::cin >> fahrradCount;

  std::vector<std::unique_ptr<Vehicle>> fahrzeuge;

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
    fahrzeuge.push_back(std::make_unique<Bicycle>(name, maxGeschwindigkeit));
  }

  std::cout << "\n已生成的车辆信息:\n";
  Vehicle::displayHeader();
  for (const auto &fahrzeug : fahrzeuge) {
    //    fahrzeug->displayData();
    //    std::cout << std::endl;
    std::cout << *fahrzeug;
    std::cout << std::endl;
  }

  double simTimeStep = 0.5;         // 每个时间步增加0.5小时
  double totalSimulationTime = 8.0; // 总模拟时间5小时
  double lastRefuelTime = 0.0;      // 上次加油的时间

  while (globalTime < totalSimulationTime) {
    // 增加全局时间
    globalTime += simTimeStep;

    // 模拟每个车辆的状态
    for (auto &fahrzeug : fahrzeuge) {
      fahrzeug->executeSimulation();
    }

    // 输出车辆的当前状态
    Vehicle::displayHeader();
    for (auto &fahrzeug : fahrzeuge) {
      std::cout << *fahrzeug;
      std::cout << std::endl;
    }

    if (std::fabs(globalTime - lastRefuelTime - refuelInterval) < epsilon ||
        globalTime > lastRefuelTime + refuelInterval) {
      std::cout << "\n达到 " << lastRefuelTime + refuelInterval
                << " 小时，为所有汽车加满油。\n";
      for (auto &fahrzeug : fahrzeuge) {
        // 尝试加油
        PKW *pkw = dynamic_cast<PKW *>(fahrzeug.get());
        if (pkw) {
          double fuelAdded = pkw->fillTank();
          std::cout << pkw->getName() << " 加油: " << fuelAdded << " 升\n";
        }
      }
      lastRefuelTime += refuelInterval;
    }

    std::cout << "当前时间: " << std::fixed << std::setprecision(2)
              << globalTime << " 小时" << std::endl;
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
  Vehicle fz1("Auto 1", 120.0);
  Vehicle fz2("Auto 2", 150.0);

  std::cout << "初始状态:" << std::endl;
  Vehicle::displayHeader();
  std::cout << fz1 << std::endl;
  std::cout << fz2 << std::endl;

  fz1 = fz2; // 将 fz2 赋值给 fz1

  std::cout << "\n赋值后的状态:" << std::endl;
  Vehicle::displayHeader();
  std::cout << fz1 << std::endl;
  std::cout << fz2 << std::endl;

  double simTimeStep = 0.5;         // 每个时间步增加0.5小时
  double totalSimulationTime = 8.0; // 总模拟时间5小时

  while (globalTime < totalSimulationTime) {
    globalTime += simTimeStep;
    fz1.executeSimulation();
    fz2.executeSimulation();

    Vehicle::displayHeader();
    std::cout << fz1 << std::endl;
    std::cout << fz2 << std::endl;

    std::cout << "当前时间: " << std::fixed << std::setprecision(2)
              << globalTime << " 小时" << std::endl;
    std::cout << "--------------------------------------------" << std::endl;
    std::cout << std::endl;
  }
}

void vAufgabe_4() {
  // 创建一个 Weg 对象，名称为"Autobahn"，长度为100，默认速度限制为无限制
  Weg autobahn("Autobahn", 100.0, SpeedRestriction::Unlimited);
  Weg::displayHeader();
  std::cout << autobahn << std::endl;
}

void vAufgabe_5() {
  Weg weg("Landstrasse", 100.0); // 100 长度的路径 Landstrasse

  std::unique_ptr<Vehicle> bmw = std::make_unique<PKW>("BMW", 120.0);
  std::unique_ptr<Vehicle> audi = std::make_unique<PKW>("Audi", 130.0);
  std::unique_ptr<Vehicle> bmx = std::make_unique<Bicycle>("BMX", 25.0);

  weg.addVehicle(std::move(bmw), 1.0);
  weg.addVehicle(std::move(audi), 1.0);
  weg.addVehicle(std::move(bmx), 1.0);

  std::cout << "\n模拟路径上的车辆行驶：" << std::endl;

  // 模拟一段时间，假设总模拟时间为10小时，每次递增0.5小时
  const double zeitschritt = 0.5; // 每次增加0.5小时
  const double simzeit = 5.0;     // 总模拟时间为10小时
  int round = 1;

  while (globalTime <= simzeit) {
    // 调用每个车辆的模拟函数
    std::cout << "Round " << round << " 开始" << std::endl;

    weg.executeSimulation();
    Weg::displayHeader();
    std::cout << weg << std::endl; // 输出每一步仿真后的路径状态
    // 输出车辆的当前状态
    Vehicle::displayHeader();
    for (auto &fahrzeug : weg.getFahrzeuge()) {
      std::cout << *fahrzeug;
      std::cout << std::endl;
    }
    // 输出当前时间（用于跟踪时间进度）
    std::cout << "当前时间: " << std::fixed << std::setprecision(2)
              << globalTime << " 小时" << std::endl;
    std::cout << "--------------------------------------" << std::endl;
    // 增加全局时钟
    globalTime += zeitschritt;
    round++;
  }
}

void vAufgabe_6() {
  bInitialisiereGrafik(800, 500);

  // 创建两条路径，一条有乡村道路限速100 km/h，一条市区道路限速50 km/h
  Weg landstrasse("LandstrasseHin", 500.0, SpeedRestriction::RuralRoad);
  Weg innerorts("LandstrasseRueck", 500.0, SpeedRestriction::UrbanArea);

  std::unique_ptr<PKW> bmw =
      std::make_unique<PKW>("BMW", 120.0); // 最大速度120 km/h
  std::unique_ptr<PKW> audi =
      std::make_unique<PKW>("Audi", 130.0); // 最大速度130 km/h

  // 将车辆添加到路径上
  landstrasse.addVehicle(std::move(bmw));
  innerorts.addVehicle(std::move(audi), 1.0);

  // 设置往返道路的图形
  int koordHin[] = {700, 250, 100, 250};   // 往道路的坐标
  int koordRueck[] = {100, 300, 700, 300}; // 返道路的坐标
  bZeichneStrasse("LandstrasseHin", "LandstrasseRueck", 500, 2, koordHin);
  bZeichneStrasse("LandstrasseRueck", "LandstrasseHin", 500, 2, koordRueck);

  // 模拟一段时间，假设总模拟时间为1小时，每次递增0.5小时
  const double zeitschritt = 0.5;
  const double simzeit = 3.0;

  while (globalTime <= simzeit) {
    std::cout << "当前时间: " << globalTime << " 小时" << std::endl;
    vSetzeZeit(globalTime);

    landstrasse.executeSimulation();
    innerorts.executeSimulation();

    Vehicle::displayHeader();
    for (auto &fahrzeug : landstrasse.getFahrzeuge()) {
      std::cout << *fahrzeug;
      std::cout << std::endl;
    }
    for (auto &fahrzeug : innerorts.getFahrzeuge()) {
      std::cout << *fahrzeug;
      std::cout << std::endl;
    }
    std::cout << "==================车辆信息Finished=================="
              << std::endl;

    Weg::displayHeader();
    std::cout << landstrasse << std::endl; // 输出乡村道路上的车辆状态
    std::cout << innerorts << std::endl;   // 输出市区道路上的车辆状态
    std::cout << "==================================" << std::endl;
    std::cout << "==================================" << std::endl;
    globalTime += zeitschritt;
  }
}

void vAufgabe_6_1() {
  bInitialisiereGrafik(800, 500);

  // 创建两条路径，一条有乡村道路限速100 km/h，一条市区道路限速50 km/h
  Weg landstrasse("LandstrasseHin", 500.0, SpeedRestriction::RuralRoad);
  Weg innerorts("LandstrasseRueck", 500.0, SpeedRestriction::UrbanArea);

  std::unique_ptr<PKW> bmw =
      std::make_unique<PKW>("BMW", 120.0); // 最大速度120 km/h
  std::unique_ptr<PKW> audi =
      std::make_unique<PKW>("Audi", 130.0); // 最大速度130 km/h

  // 将车辆添加到路径上
  landstrasse.addVehicle(std::move(bmw));
  innerorts.addVehicle(std::move(audi), 1.0);

  // 设置往返道路的图形
  int koordHin[] = {700, 250, 100, 250};   // 往道路的坐标
  int koordRueck[] = {100, 300, 700, 300}; // 返道路的坐标
  bZeichneStrasse("LandstrasseHin", "LandstrasseRueck", 500, 2, koordHin);
  bZeichneStrasse("LandstrasseRueck", "LandstrasseHin", 500, 2, koordRueck);

  // 模拟一段时间，假设总模拟时间为1小时，每次递增0.5小时
  const double zeitschritt = 0.5;
  const double simzeit = 3.0;

  while (globalTime <= simzeit) {
    std::cout << "当前时间: " << globalTime << " 小时" << std::endl;
    vSetzeZeit(globalTime);

    landstrasse.executeSimulation();
    innerorts.executeSimulation();

    Vehicle::displayHeader();
    for (auto &fahrzeug : landstrasse.getFahrzeuge()) {
      //            double relPos = fahrzeug->dGetRelPosition(); //
      //            获取车辆在路径上的相对位置 double kmh =
      //            fahrzeug->getMaxSpeed(); double tank =
      //            fahrzeug->dTankinhalt();
      std::cout << *fahrzeug;
      std::cout << std::endl;
    }
    for (auto &fahrzeug : innerorts.getFahrzeuge()) {
      std::cout << *fahrzeug;
      std::cout << std::endl;
    }
    std::cout << "==================车辆信息Finished=================="
              << std::endl;

    Weg::displayHeader();
    std::cout << landstrasse << std::endl; // 输出乡村道路上的车辆状态
    std::cout << innerorts << std::endl;   // 输出市区道路上的车辆状态
    std::cout << "==================================" << std::endl;
    std::cout << "==================================" << std::endl;
    vSleep(500);

    globalTime += zeitschritt;
  }
  vBeendeGrafik();
}

void vAufgabe_6_2() {
  // 初始化图形窗口
  bInitialisiereGrafik(800, 500);

  // 设置路径的长度
  const double laenge = 500.0;

  // 绘制往返路径
  int koord[] = {100, 250, 700, 250}; // 线段的起点和终点坐标
  bZeichneStrasse("Patn", "ReturnPath", laenge, 2, koord);
  bZeichneKreuzung(200, 200);
  // 创建车辆并设置其属性
  std::unique_ptr<Vehicle> bmw = std::make_unique<Vehicle>("BMW", 120.0);
  double relPosition = 0.0; // 相对位置
  double kmH = 0.0;         // 速度
  double tank = 50.0;       // 油箱容量

  // 绘制车辆（在路径上位置为0，初始速度和油量）
  bZeichnePKW(bmw->getName(), "Patn", relPosition, kmH, tank);

  // 暂停以便查看
  vSleep(2000); // 暂停2000毫秒

  // 结束图形连接
  vBeendeGrafik();
}

void vAufgabe_6_3() {
  // 初始化图形窗口
  const int windowWidth = 800;
  const int windowHeight = 500;
  if (!bInitialisiereGrafik(windowWidth, windowHeight)) {
    std::cerr << "图形界面初始化失败！" << std::endl;
    return;
  }

  // 设置路径
  Weg hin("Hin", 100.0, SpeedRestriction::Unlimited);
  Weg rueck("Rueck", 100.0, SpeedRestriction::Unlimited);

  int koordHin[] = {100, 250, 700, 250}; // 往路径坐标
  //  int koordRueck[] = {700, 250, 100, 250}; // 返路径坐标
  bZeichneStrasse(hin.getName(), rueck.getName(), hin.getLaenge(), 2, koordHin);
  //  bZeichneStrasse(rueck.getName(), hin.getName(), rueck.getLaenge(), 2,
  //                  koordRueck);
  // 创建车辆
  std::unique_ptr<PKW> bmw = std::make_unique<PKW>("BMW", 120.0, 1, 50.0);
  std::unique_ptr<Bicycle> trek = std::make_unique<Bicycle>("Trek", 25.0);
  std::unique_ptr<PKW> audi = std::make_unique<PKW>("Audi", 100.0, 1, 60.0);

  // 将车辆添加到路径上
  hin.addVehicle(std::move(bmw));
  hin.addVehicle(std::move(trek), 1.0); // 将自行车设置为延迟1小时后开始
  rueck.addVehicle(std::move(audi));

  // 模拟一段时间，假设总模拟时间为1小时，每次递增0.5小时
  const double zeitschritt = 0.5;
  const double simzeit = 7;

  while (globalTime <= simzeit) {
    std::cout << "当前时间: " << globalTime << " 小时" << std::endl;
    vSetzeZeit(globalTime);

    hin.executeSimulation();
    rueck.executeSimulation();

    Vehicle::displayHeader();
    for (auto &fahrzeug : hin.getFahrzeuge()) {
      std::cout << *fahrzeug;
      std::cout << std::endl;
    }
    for (auto &fahrzeug : rueck.getFahrzeuge()) {
      std::cout << *fahrzeug;
      std::cout << std::endl;
    }
    std::cout << "==================车辆信息Finished=================="
              << std::endl;

    Weg::displayHeader();
    std::cout << hin << std::endl;
    std::cout << rueck << std::endl;
    std::cout << "==================================" << std::endl;
    std::cout << "==================================" << std::endl;
    globalTime += zeitschritt;
    vSleep(1000); // 暂停2000毫秒
  }

  // 结束图形会话
  vBeendeGrafik();
}

void vAufgabe_6a() {
  // 初始化随机数生成器
  static std::mt19937 device(0); // 固定种子以获得可复现的结果
  std::uniform_int_distribution<int> dist(1, 10);

  // 创建一个延迟列表
  deferred::DeferredList<int> liste;

  // 填充列表，生成 10 个随机整数
  for (int i = 0; i < 10; ++i) {
    int zuf = dist(device);
    liste.push_back(zuf);
  }
  liste.applyActionToList();

  // 输出列表
  std::cout << "Initial list: ";
  for (const auto &item : liste) {
    std::cout << item << " ";
  }
  std::cout << std::endl;

  // 删除所有大于 5 的元素
  for (auto it = liste.begin(); it != liste.end(); it++) {
    if (*it > 5) {
      liste.erase(it);
    }
  }

  // 输出列表（更新尚未执行，输出应相同）
  std::cout << "List after deletion (before update): ";
  for (const auto &item : liste) {
    std::cout << item << " ";
  }
  std::cout << std::endl;

  // 调用 vAktualisieren() 来更新列表
  liste.applyActionToList();

  // 输出列表（此时列表应已更改）
  std::cout << "List after update: ";
  for (const auto &item : liste) {
    std::cout << item << " ";
  }
  std::cout << std::endl;

  // 在列表开头和末尾插入两个随机值
  liste.push_front(dist(device)); // 随机值插入开头
  liste.push_back(dist(device));  // 随机值插入末尾

  // 再次输出列表进行检查
  std::cout << "Final list after inserting two random values: ";
  for (const auto &item : liste) {
    std::cout << item << " ";
  }
  std::cout << std::endl;
  // 调用 vAktualisieren() 来更新列表
  liste.applyActionToList();

  // 输出列表（此时列表应已更改）
  std::cout << "List after update: ";
  for (const auto &item : liste) {
    std::cout << item << " ";
  }
  std::cout << std::endl;
}

int main() {
  vAufgabe_6_3();
  std::cout << "\n=== 程序结束 ===" << std::endl;
  return 0;
}
