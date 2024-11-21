#include "Weg.h"
#include "Fahrzeug.h"
#include "Fahrzeugausnahme.h"

Weg::Weg()
    : Simulationsobjekt(""), p_dLaenge(0.0),
      p_eTempolimit(Tempolimit::Unlimited) {}

Weg::Weg(const std::string &name, double laenge, Tempolimit tempolimit)
    : Simulationsobjekt(name), p_dLaenge(laenge), p_eTempolimit(tempolimit) {}

void Weg::vAnnahme(std::unique_ptr<Vehicle> pFzg) {
  // 使用 move 将车辆移动到车辆列表
  pFzg->vNeueStrecke(*this);
  m_vehicleList.push_back(std::move(pFzg));
  //  m_vehicleList.vAktualisieren();
  // 获取最后添加的车辆，通知它新的路径
  //  auto lastElement = std::prev(m_vehicleList.end());
  //  std::cout << "Vehicle " << (*lastElement)->getName() << " 被添加到路径 "
  //            << p_sName << " 上。\n";
}

void Weg::vAnnahme(std::unique_ptr<Vehicle> pVehicle, double dStartzeit) {
  pVehicle->vNeueStrecke(*this, dStartzeit);     // 设置停放行为
  m_vehicleList.push_front(std::move(pVehicle)); // 添加到列表前端
  m_vehicleList.applyActionToList();
  std::cout << "Vehicle " << (*m_vehicleList.begin())->getName()
            << " 被添加到路径 " << p_sName << " 上， 停放时间为 " << dStartzeit
            << " 小时\n";
}

std::unique_ptr<Vehicle> Weg::pAbgabe(const Vehicle &Fahrzeug) {
  // 注意：it现在是指向指针的指针
  auto it = std::find_if(
      m_vehicleList.begin(), m_vehicleList.end(),
      [&](const std::unique_ptr<Vehicle> &f) { return f && *f == Fahrzeug; });

  // 如果找到该车辆
  if (it != m_vehicleList.end()) {
    // 将找到的车辆移到局部变量并从列表中删除
    std::unique_ptr<Vehicle> abgabeVehicle = std::move(*it);
    m_vehicleList.erase(it); // 从列表中删除

    // 返回局部存储的指针
    return abgabeVehicle;
  }

  // 如果未找到，返回空指针
  return nullptr;
}

void Weg::vSimulieren() {
  m_vehicleList.applyActionToList();
  for (const auto &fzg : m_vehicleList) {
    try {
      fzg->vSimulieren();
      fzg->vZeichnen(*this); // 绘制车辆
    } catch (const VehicleException &ex) {
      ex.handleException(); // 调用异常的处理函数
    }
  }
  m_vehicleList.applyActionToList();

  //  for (auto it = m_vehicleList.begin(); it != m_vehicleList.end();) {
  //    try {
  //      (*it)->vSimulieren();
  //      (*it)->vZeichnen(*this);
  //      ++it; // 手动增量，以避免在添加或删除元素时失效
  //    } catch (const Vehicleausnahme &ex) {
  //      ex.vBearbeiten();
  //      it = m_vehicleList.erase(it); //
  //      在发生异常时从列表中删除对象，并更新迭代器
  //    }
  //  }
}

void Weg::vAusgeben(std::ostream &os) const {
  Simulationsobjekt::vAusgeben();
  std::cout << std::resetiosflags(std::ios::adjustfield)
            << std::setiosflags(std::ios::left);
  os << std::setw(10) << p_dLaenge << " | ";
  // 输出车辆列表
  os << "(";
  for (auto it = m_vehicleList.begin(); it != m_vehicleList.end(); ++it) {
    if (it != m_vehicleList.begin()) {
      os << ", ";
    }
    os << (*it)->getName();
  }
  os << ")";
}

void Weg::vAusgeben() const {
  Simulationsobjekt::vAusgeben();
  std::cout << std::resetiosflags(std::ios::adjustfield)
            << std::setiosflags(std::ios::left);
  std::cout << std::setw(10) << p_dLaenge << " : ";

  std::cout << "(";
  for (auto it = m_vehicleList.begin(); it != m_vehicleList.end(); ++it) {
    if (it != m_vehicleList.begin()) {
      std::cout << ", ";
    }
    std::cout << (*it)->getName();
  }
  std::cout << ")";
}

double Weg::dGetTempolimit() const {
  switch (p_eTempolimit) {
  case Tempolimit::Unlimited:
    return std::numeric_limits<double>::max(); // 无速度限制
  case Tempolimit::Landstrasse:
    return 100.0; // 乡村道路限速100 km/h
  case Tempolimit::Innerorts:
    return 50.0; // 市区道路限速50 km/h
  default:
    return std::numeric_limits<double>::max();
  }
}

void Weg::vKopf() {
  std::cout << std::resetiosflags(std::ios::adjustfield)
            << std::setiosflags(std::ios::left);
  std::cout << std::setw(5) << "ID" << " | " << std::setw(15) << "Name" << " | "
            << std::setw(10) << "Length" << " | " << std::setw(10) << "Vehiclee"
            << std::endl;
  std::cout << "-------------------------------------------------------"
            << std::endl;
}
