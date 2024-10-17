#include "Weg.h"
#include "Fahrzeug.h"

Weg::Weg()
    : Simulationsobjekt(""), p_dLaenge(0.0),
      p_eTempolimit(Tempolimit::Autobahn) {}

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

void Weg::vSimulieren() {
  for (auto &fahrzeug : p_pFahrzeuge) {
    fahrzeug->vSimulieren();
  }
}

void Weg::vAusgeben(std::ostream &os) const {
  Simulationsobjekt::vAusgeben();
  std::cout << std::resetiosflags(std::ios::adjustfield)
            << std::setiosflags(std::ios::left);
  os << " : " << std::setw(10) << p_dLaenge << " | ";
  // 输出车辆列表
  os << "(";
  for (auto it = p_pFahrzeuge.begin(); it != p_pFahrzeuge.end(); ++it) {
    if (it != p_pFahrzeuge.begin()) {
      os << ", "; // 车辆之间添加逗号和空格
    }
    os << (*it)->getName();
  }
  os << ")";
}

void Weg::vAusgeben() const {
  Simulationsobjekt::vAusgeben();
  std::cout << std::resetiosflags(std::ios::adjustfield)
            << std::setiosflags(std::ios::left);
  std::cout << " : " << std::setw(10) << p_dLaenge << " : ";
  // 输出车辆列表
  std::cout << "(";
  for (auto it = p_pFahrzeuge.begin(); it != p_pFahrzeuge.end(); ++it) {
    if (it != p_pFahrzeuge.begin()) {
      std::cout << ", ";
    }
    std::cout << (*it)->getName();
  }
  std::cout << ")";
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
