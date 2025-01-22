﻿#include "Weg.h"
#include "Fahrzeug.h"
#include "Fahrzeugausnahme.h"
#include "pkw.h"

Weg::Weg()
    : Simulationsobjekt(""), p_dLaenge(0.0),
      p_eTempolimit(Tempolimit::Unlimited) {}

Weg::Weg( const std::string& name, double laenge, Tempolimit tempolimit, bool ueberholverbot )
    : Simulationsobjekt( name ), p_dLaenge( laenge ), p_eTempolimit( tempolimit ), bUeberholverbot( ueberholverbot ) {}

Weg::Weg( const std::string& name, double laenge, std::shared_ptr< Kreuzung > pStart, Tempolimit tempolimit, bool ueberholverbot )
    : Simulationsobjekt( name ), p_dLaenge( laenge ), pStartKreuzung( std::move( pStart ) ), pEndKreuzung(), p_eTempolimit( tempolimit ), bUeberholverbot( ueberholverbot ) {}

Weg::Weg( const std::string& name, double laenge, std::shared_ptr< Kreuzung > pStart, std::shared_ptr< Kreuzung > pEnd, Tempolimit tempolimit, bool ueberholverbot )
    : Simulationsobjekt( name ), p_dLaenge( laenge ), pStartKreuzung( std::move( pStart ) ), pEndKreuzung( std::move( pEnd ) ), p_eTempolimit( tempolimit ), bUeberholverbot( ueberholverbot ) {}

void Weg::vAnnahme(std::unique_ptr<Fahrzeug> pFzg) {
  // 使用 move 将车辆移动到车辆列表
  pFzg->vNeueStrecke(*this);
  p_pFahrzeuge.push_back( std::move( pFzg ) );
  // 获取最后添加的车辆，通知它新的路径
  //  auto lastElement = std::prev(p_pFahrzeuge.end());
  //  std::cout << "Fahrzeug " << (*lastElement)->getName() << " 被添加到路径 "
  //            << p_sName << " 上。\n";
}

void Weg::vAnnahme(std::unique_ptr<Fahrzeug> pFahrzeug, double dStartzeit) {
  pFahrzeug->vNeueStrecke(*this, dStartzeit);    // 设置停放行为
  p_pFahrzeuge.push_front(std::move(pFahrzeug)); // 添加到列表前端
  p_pFahrzeuge.vAktualisieren();
  std::cout << "Fahrzeug " << (*p_pFahrzeuge.begin())->getName()
            << " 被添加到路径 " << p_sName << " 上， 停放时间为 " << dStartzeit
            << " 小时\n";
}

std::unique_ptr<Fahrzeug> Weg::pAbgabe(const Fahrzeug &fahrzeug) {
  // 注意：it现在是指向指针的指针
  auto it = std::find_if(
      p_pFahrzeuge.begin(), p_pFahrzeuge.end(),
      [&](const std::unique_ptr<Fahrzeug> &f) { return f && *f == fahrzeug; });

  // 如果找到该车辆
  if (it != p_pFahrzeuge.end()) {
    // 将找到的车辆移到局部变量并从列表中删除
    std::unique_ptr<Fahrzeug> abgabeFahrzeug = std::move(*it);
    p_pFahrzeuge.erase(it); // 从列表中删除

    // 返回局部存储的指针
    return abgabeFahrzeug;
  }

  // 如果未找到，返回空指针
  return nullptr;
}

void Weg::vSimulieren() {
  p_pFahrzeuge.vAktualisieren();
  for (const auto &fzg : p_pFahrzeuge) {
    try {
      fzg->vSimulieren();
      fzg->vZeichnen(*this); // 绘制车辆
    } catch (const Fahrzeugausnahme &ex) {
      ex.vBearbeiten(); // 调用异常的处理函数
    }
  }
  p_pFahrzeuge.vAktualisieren();
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

// 给你一辆车，返回他的虚拟位置（前一辆车的位置）
double Weg::getBarriere( const Fahrzeug& faz ) {
  if ( bUeberholverbot == false ) {
    return p_dLaenge;
  }

  // 第三个参数 叫做 C++11中的lambda表达式
  auto it = std::find_if( p_pFahrzeuge.begin(), p_pFahrzeuge.end(), [ & ]( const std::unique_ptr< Fahrzeug >& f ) { return f && *f == faz; } );

  // 已经找到车了,并且这是第一辆车，并且他前面没有停放的停放的车辆
  if ( it == p_pFahrzeuge.begin() ) {
    return p_dLaenge;
  }

  // 获取前一辆车的位置, 利用了我们的list底层是一个双向链表
  // 如果前一辆是停放的话（也就是abs距离为0），就返回路径长度；否则，返回前一辆车的已行驶距离
  auto prevFaz = std::prev( it );

  // 如果车辆抛锚，再返回前一个位置
  // 4 <-- 3  <-- 2
  while ( true ) {
    PKW* pkw = dynamic_cast< PKW* >( prevFaz->get() );
    if ( !pkw || pkw->getTankinhalt() > 0 ) {
      break;
    }
    if ( prevFaz == p_pFahrzeuge.begin() ) {
      return p_dLaenge;
    }
    prevFaz = std::prev( prevFaz );
  }
  return ( *prevFaz )->getAbschnittStrecke() == 0 ? p_dLaenge : ( *prevFaz )->getAbschnittStrecke();
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
