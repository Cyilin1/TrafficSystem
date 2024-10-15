#include "Simulationsobjekt.h"

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

void Aufgabe_1() {
  std::cout << "=== 静态对象创建 ===" << std::endl;
  Fahrzeug fahrzeug1("Auto A"); // 静态对象
  Fahrzeug fahrzeug2;           // 静态对象，名称为空

  std::cout << "\n=== 动态对象创建 ===" << std::endl;
  Fahrzeug *fahrzeug3 = new Fahrzeug("Auto B"); // 动态对象
  Fahrzeug *fahrzeug4 = new Fahrzeug();         // 动态对象，名称为空

  std::cout << "\n=== 动态对象删除 ===" << std::endl;
  delete fahrzeug3;
  delete fahrzeug4;

  std::cout << "\n=== 使用智能指针 ===" << std::endl;
  // 使用 unique_ptr
  std::unique_ptr<Fahrzeug> uniqueFahrzeug =
      std::make_unique<Fahrzeug>("Auto C");

  // 使用 shared_ptr
  std::shared_ptr<Fahrzeug> sharedFahrzeug1 =
      std::make_shared<Fahrzeug>("Auto D");
  std::shared_ptr<Fahrzeug> sharedFahrzeug2 = sharedFahrzeug1; // 共享所有权

  std::cout << "sharedFahrzeug1 的引用计数: " << sharedFahrzeug1.use_count()
            << std::endl;

  // unique_ptr 不能被复制，只能被移动
  std::unique_ptr<Fahrzeug> uniqueFahrzeug2 =
      std::make_unique<Fahrzeug>("Auto E");
  // std::unique_ptr<Fahrzeug> uniqueFahrzeug3 = uniqueFahrzeug2; //
  // 错误：不能复制
  std::unique_ptr<Fahrzeug> uniqueFahrzeug3 =
      std::move(uniqueFahrzeug2); // 移动所有权

  if (!uniqueFahrzeug2) {
    std::cout << "uniqueFahrzeug2 已被移动，当前为空。" << std::endl;
  }

  std::cout << "\n=== 存储 unique_ptr<Fahrzeug> 在 vector 中 ===" << std::endl;
  std::vector<std::unique_ptr<Fahrzeug>> fahrzeugVector;

  fahrzeugVector.push_back(std::make_unique<Fahrzeug>("Auto F"));
  fahrzeugVector.push_back(std::make_unique<Fahrzeug>("Auto G"));
  fahrzeugVector.push_back(std::make_unique<Fahrzeug>()); // 名称为空

  std::cout << "当前 vector 中有 " << fahrzeugVector.size()
            << " 个 Fahrzeug 对象。" << std::endl;

  std::cout << "\n=== 清空 vector ===" << std::endl;
  fahrzeugVector.clear(); // 删除所有 unique_ptr<Fahrzeug>，触发析构函数
  std::cout << "vector 已清空。" << std::endl;

  // 创建一个 vector 用于存储 shared_ptr<Fahrzeug> 对象
  std::vector<std::shared_ptr<Fahrzeug>> fahrzeugSharedVector;

  // 使用 make_shared 创建两个 Fahrzeug 对象并加入向量中
  std::shared_ptr<Fahrzeug> fz1 = std::make_shared<Fahrzeug>();
  std::shared_ptr<Fahrzeug> fz2 = std::make_shared<Fahrzeug>();

  fahrzeugSharedVector.push_back(fz1);
  fahrzeugSharedVector.push_back(fz2);

  // 输出引用计数
  std::cout << "Reference count for fz1: " << fz1.use_count()
            << std::endl; // 2 (vector 和 fz1 持有)
  std::cout << "Reference count for fz2: " << fz2.use_count()
            << std::endl; // 2 (vector 和 fz2 持有)

  // 将 fz1 进行移动操作
  std::shared_ptr<Fahrzeug> fz3 = std::move(fz1);
  std::cout << "After move, reference count for fz3: " << fz3.use_count()
            << std::endl; // 2
  std::cout << "After move, reference count for fz1: " << fz1.use_count()
            << std::endl; // 0 (fz1 为空)

  // 再次输出 vector 中对象的引用计数
  std::cout << "Reference count for fz2 in vector: "
            << fahrzeugSharedVector[1].use_count() << std::endl;

  // 调试时可以观察析构函数被调用的情况
  fahrzeugSharedVector.clear(); // 清空向量，应该调用对象的析构函数
  std::cout << "Vector cleared.\n";
}

void Aufgabe_1_1() {
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

void Aufgabe_1a0() {
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

void Aufgabe_2() {
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

int main() {
  vAufgabe_3();
  std::cout << "\n=== 程序结束 ===" << std::endl;
  return 0;
}
