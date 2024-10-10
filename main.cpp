#include "Fahrzeug.h"

#include <iostream>
#include <string>
#include <vector>
int Fahrzeug::p_iMaxID = 0;

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

int main() {
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
  std::cout << "\n=== 程序结束 ===" << std::endl;
  return 0;
}
