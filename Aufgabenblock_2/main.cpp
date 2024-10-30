#include "SimuClient.h"
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
  Weg autobahn("Autobahn", 100.0, Tempolimit::Unlimited);
  Weg::vKopf();
  std::cout << autobahn << std::endl;
}

void vAufgabe_5() {
  Weg weg("Landstrasse", 100.0); // 100 长度的路径 Landstrasse

  std::unique_ptr<Fahrzeug> bmw = std::make_unique<PKW>("BMW", 120.0);
  std::unique_ptr<Fahrzeug> audi = std::make_unique<PKW>("Audi", 130.0);
  std::unique_ptr<Fahrzeug> bmx = std::make_unique<Fahrrad>("BMX", 25.0);

  weg.vAnnahme(std::move(bmw), 1.0);
  weg.vAnnahme(std::move(audi), 1.0);
  weg.vAnnahme(std::move(bmx), 1.0);

  std::cout << "\n模拟路径上的车辆行驶：" << std::endl;

  // 模拟一段时间，假设总模拟时间为10小时，每次递增0.5小时
  const double zeitschritt = 0.5; // 每次增加0.5小时
  const double simzeit = 5.0;     // 总模拟时间为10小时
  int round = 1;

  while (d_GlobaleZeit <= simzeit) {
    // 调用每个车辆的模拟函数
    std::cout << "Round " << round << " 开始" << std::endl;

    weg.vSimulieren();
    Weg::vKopf();
    std::cout << weg << std::endl; // 输出每一步仿真后的路径状态
    // 输出车辆的当前状态
    Fahrzeug::vKopf();
    for (auto &fahrzeug : weg.getFahrzeuge()) {
      std::cout << *fahrzeug;
      std::cout << std::endl;
    }
    // 输出当前时间（用于跟踪时间进度）
    std::cout << "当前时间: " << std::fixed << std::setprecision(2)
              << d_GlobaleZeit << " 小时" << std::endl;
    std::cout << "--------------------------------------" << std::endl;
    // 增加全局时钟
    d_GlobaleZeit += zeitschritt;
    round++;
  }
}

void vAufgabe_6() {
  bInitialisiereGrafik(800, 500);

  // 创建两条路径，一条有乡村道路限速100 km/h，一条市区道路限速50 km/h
  Weg landstrasse("LandstrasseHin", 500.0, Tempolimit::Landstrasse);
  Weg innerorts("LandstrasseRueck", 500.0, Tempolimit::Innerorts);

  std::unique_ptr<PKW> bmw =
      std::make_unique<PKW>("BMW", 120.0); // 最大速度120 km/h
  std::unique_ptr<PKW> audi =
      std::make_unique<PKW>("Audi", 130.0); // 最大速度130 km/h

  // 将车辆添加到路径上
  landstrasse.vAnnahme(std::move(bmw));
  innerorts.vAnnahme(std::move(audi), 1.0);

  // 设置往返道路的图形
  int koordHin[] = {700, 250, 100, 250};   // 往道路的坐标
  int koordRueck[] = {100, 300, 700, 300}; // 返道路的坐标
  bZeichneStrasse("LandstrasseHin", "LandstrasseRueck", 500, 2, koordHin);
  bZeichneStrasse("LandstrasseRueck", "LandstrasseHin", 500, 2, koordRueck);

  // 模拟一段时间，假设总模拟时间为1小时，每次递增0.5小时
  const double zeitschritt = 0.5;
  const double simzeit = 3.0;

  while (d_GlobaleZeit <= simzeit) {
    std::cout << "当前时间: " << d_GlobaleZeit << " 小时" << std::endl;
    vSetzeZeit(d_GlobaleZeit);

    landstrasse.vSimulieren();
    innerorts.vSimulieren();

    Fahrzeug::vKopf();
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

    Weg::vKopf();
    std::cout << landstrasse << std::endl; // 输出乡村道路上的车辆状态
    std::cout << innerorts << std::endl;   // 输出市区道路上的车辆状态
    std::cout << "==================================" << std::endl;
    std::cout << "==================================" << std::endl;
    d_GlobaleZeit += zeitschritt;
  }
}

void vAufgabe_6_1() {
  bInitialisiereGrafik(800, 500);

  // 创建两条路径，一条有乡村道路限速100 km/h，一条市区道路限速50 km/h
  Weg landstrasse("LandstrasseHin", 500.0, Tempolimit::Landstrasse);
  Weg innerorts("LandstrasseRueck", 500.0, Tempolimit::Innerorts);

  std::unique_ptr<PKW> bmw =
      std::make_unique<PKW>("BMW", 120.0); // 最大速度120 km/h
  std::unique_ptr<PKW> audi =
      std::make_unique<PKW>("Audi", 130.0); // 最大速度130 km/h

  // 将车辆添加到路径上
  landstrasse.vAnnahme(std::move(bmw));
  innerorts.vAnnahme(std::move(audi), 1.0);

  // 设置往返道路的图形
  int koordHin[] = {700, 250, 100, 250};   // 往道路的坐标
  int koordRueck[] = {100, 300, 700, 300}; // 返道路的坐标
  bZeichneStrasse("LandstrasseHin", "LandstrasseRueck", 500, 2, koordHin);
  bZeichneStrasse("LandstrasseRueck", "LandstrasseHin", 500, 2, koordRueck);

  // 模拟一段时间，假设总模拟时间为1小时，每次递增0.5小时
  const double zeitschritt = 0.5;
  const double simzeit = 3.0;

  while (d_GlobaleZeit <= simzeit) {
    std::cout << "当前时间: " << d_GlobaleZeit << " 小时" << std::endl;
    vSetzeZeit(d_GlobaleZeit);

    landstrasse.vSimulieren();
    innerorts.vSimulieren();

    Fahrzeug::vKopf();
    for (auto &fahrzeug : landstrasse.getFahrzeuge()) {
      //            double relPos = fahrzeug->dGetRelPosition(); //
      //            获取车辆在路径上的相对位置 double kmh =
      //            fahrzeug->dGeschwindigkeit(); double tank =
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

    Weg::vKopf();
    std::cout << landstrasse << std::endl; // 输出乡村道路上的车辆状态
    std::cout << innerorts << std::endl;   // 输出市区道路上的车辆状态
    std::cout << "==================================" << std::endl;
    std::cout << "==================================" << std::endl;
    vSleep(500);

    d_GlobaleZeit += zeitschritt;
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
  std::unique_ptr<Fahrzeug> bmw = std::make_unique<Fahrzeug>("BMW", 120.0);
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
  Weg hin("Hin", 100.0, Tempolimit::Unlimited);
  Weg rueck("Rueck", 100.0, Tempolimit::Unlimited);

  int koordHin[] = {100, 250, 700, 250}; // 往路径坐标
  //  int koordRueck[] = {700, 250, 100, 250}; // 返路径坐标
  bZeichneStrasse(hin.getName(), rueck.getName(), hin.getLaenge(), 2, koordHin);
  //  bZeichneStrasse(rueck.getName(), hin.getName(), rueck.getLaenge(), 2,
  //                  koordRueck);
  // 创建车辆
  std::unique_ptr<PKW> bmw = std::make_unique<PKW>("BMW", 120.0, 1, 50.0);
  std::unique_ptr<Fahrrad> trek = std::make_unique<Fahrrad>("Trek", 25.0);
  std::unique_ptr<PKW> audi = std::make_unique<PKW>("Audi", 100.0, 1, 60.0);

  // 将车辆添加到路径上
  hin.vAnnahme(std::move(bmw));
  hin.vAnnahme(std::move(trek), 1.0); // 将自行车设置为延迟1小时后开始
  rueck.vAnnahme(std::move(audi));

  // 模拟一段时间，假设总模拟时间为1小时，每次递增0.5小时
  const double zeitschritt = 0.5;
  const double simzeit = 7;

  while (d_GlobaleZeit <= simzeit) {
    std::cout << "当前时间: " << d_GlobaleZeit << " 小时" << std::endl;
    vSetzeZeit(d_GlobaleZeit);

    hin.vSimulieren();
    rueck.vSimulieren();

    Fahrzeug::vKopf();
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

    Weg::vKopf();
    std::cout << hin << std::endl;
    std::cout << rueck << std::endl;
    std::cout << "==================================" << std::endl;
    std::cout << "==================================" << std::endl;
    d_GlobaleZeit += zeitschritt;
    vSleep(1000); // 暂停2000毫秒
  }

  // 结束图形会话
  vBeendeGrafik();
}

int main() {
  vAufgabe_6_3();
  std::cout << "\n=== 程序结束 ===" << std::endl;
  return 0;
}
