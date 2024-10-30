#include "Weg.h"
#include "Fahrzeug.h"
#include "Fahrzeugausnahme.h"

Weg::Weg()
    : Simulationsobjekt(""), p_dLaenge(0.0),
      p_eTempolimit(Tempolimit::Unlimited) {}

Weg::Weg(const std::string &name, double laenge, Tempolimit tempolimit)
    : Simulationsobjekt(name), p_dLaenge(laenge), p_eTempolimit(tempolimit) {}

void Weg::vAnnahme(std::unique_ptr<Fahrzeug> pFzg) {
  // 使用 move 将车辆移动到车辆列表
  p_pFahrzeuge.push_back(std::move(pFzg));

  // 获取最后添加的车辆，通知它新的路径
  p_pFahrzeuge.back()->vNeueStrecke(*this);
  std::cout << "Fahrzeug " << p_pFahrzeuge.back()->getName() << " 被添加到路径 "
            << p_sName << " 上。\n";
}

void Weg::vAnnahme(std::unique_ptr<Fahrzeug> pFahrzeug, double dStartzeit) {
  pFahrzeug->vNeueStrecke(*this, dStartzeit);    // 设置停放行为
  p_pFahrzeuge.push_front(std::move(pFahrzeug)); // 添加到列表前端
  std::cout << "Fahrzeug " << p_pFahrzeuge.front()->getName()
            << " 被添加到路径 " << p_sName << " 上， 停放时间为 " << dStartzeit
            << " 小时\n";
}

void Weg::vSimulieren() {
  try {
    for (auto &fzg : p_pFahrzeuge) {
      fzg->vSimulieren();
      fzg->vZeichnen(*this); // 绘制车辆
    }
  } catch (const Fahrzeugausnahme &ex) {
    ex.vBearbeiten(); // 调用异常的处理函数
  }
}

void Weg::vAusgeben(std::ostream &os) const {
  Simulationsobjekt::vAusgeben();
  std::cout << std::resetiosflags(std::ios::adjustfield)
            << std::setiosflags(std::ios::left);
  os << std::setw(10) << p_dLaenge << " | ";
  // 输出车辆列表
  os << "(";
  for (auto it = p_pFahrzeuge.begin(); it != p_pFahrzeuge.end(); ++it) {
    if (it != p_pFahrzeuge.begin()) {
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
  for (auto it = p_pFahrzeuge.begin(); it != p_pFahrzeuge.end(); ++it) {
    if (it != p_pFahrzeuge.begin()) {
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
            << std::setw(10) << "Length" << " | " << std::setw(10)
            << "Fahrzeuge" << std::endl;
  std::cout << "-------------------------------------------------------"
            << std::endl;
}
