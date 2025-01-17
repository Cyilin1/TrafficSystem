#include "SimuClient.h"
#include "Weg.h"
#include "fahrrad.h".h "
#include "kreuzung.h"
#include "pkw.h"
#include "simulation.h"
#include "vertagt_liste.h"
#include <fstream>
#include <string>
#include <vector>

double d_GlobaleZeit = 0.0; // 定义全局时钟
const double epsilon = 1e-6;
const double refuelInterval = 3.0;

int Simulationsobjekt::p_iMaxID = 0;

///**
// * @brief 增加了超车禁令
// */
// void vAufgabe_6_4() {
//  // 初始化图形窗口
//  const int windowWidth  = 800;
//  const int windowHeight = 500;
//  if ( !bInitialisiereGrafik( windowWidth, windowHeight ) ) {
//    std::cerr << "图形界面初始化失败！" << std::endl;
//    return;
//  }

//  // 设置路径
//  Weg hin( "Hin", 100.0, Tempolimit::Unlimited, true );
//  Weg rueck( "Rueck", 100.0, Tempolimit::Unlimited );

//  int koordHin[] = { 100, 250, 700, 250 };  // 往路径坐标
//  bZeichneStrasse( hin.getName(), rueck.getName(), hin.getLaenge(), 2, koordHin );

//  // 创建车辆
//  std::unique_ptr< PKW >     bmw  = std::make_unique< PKW >( "BMW", 120.0, 1, 50.0 );
//  std::unique_ptr< Fahrrad > trek = std::make_unique< Fahrrad >( "Trek", 25.0 );
//  std::unique_ptr< PKW >     audi = std::make_unique< PKW >( "Audi", 100.0, 1, 60.0 );

//  // 将车辆添加到路径上
//  hin.vAnnahme( std::move( trek ) );
//  hin.vAnnahme( std::move( audi ) );
//  hin.vAnnahme( std::move( bmw ) );

//  // 模拟一段时间，假设总模拟时间为1小时，每次递增0.3小时
//  const double zeitschritt = 0.3;
//  const double simzeit     = 7;

//  for ( d_GlobaleZeit = 0; d_GlobaleZeit < simzeit; d_GlobaleZeit += zeitschritt ) {
//    std::cout << "当前时间: " << d_GlobaleZeit << " 小时" << std::endl;
//    vSetzeZeit( d_GlobaleZeit );

//    hin.vSimulieren();
//    rueck.vSimulieren();

//    Fahrzeug::vKopf();
//    for ( auto& fahrzeug : hin.getFahrzeuge() ) {
//      std::cout << *fahrzeug;
//      std::cout << std::endl;
//    }
//    for ( auto& fahrzeug : rueck.getFahrzeuge() ) {
//      std::cout << *fahrzeug;
//      std::cout << std::endl;
//    }
//    std::cout << "==================车辆信息Finished==================" << std::endl;

//    Weg::vKopf();
//    std::cout << hin << std::endl;
//    std::cout << rueck << std::endl;
//    std::cout << "==================================" << std::endl;
//    std::cout << "==================================" << std::endl;
//    vSleep( 1000 );  // 暂停2000毫秒
//  }

//  // 结束图形会话
//  vBeendeGrafik();
//}

void vAufgabe_7() {
  // 初始化图形窗口
  const int windowWidth  = 1000;
  const int windowHeight = 1000;
  if ( !bInitialisiereGrafik( windowWidth, windowHeight ) ) {
    std::cerr << "图形界面初始化失败！" << std::endl;
    return;
  }
  auto kreuzung1 = std::make_shared< Kreuzung >( "Kr1", 0 );
  auto kreuzung2 = std::make_shared< Kreuzung >( "Kr2", 1000.0 );
  auto kreuzung3 = std::make_shared< Kreuzung >( "Kr3", 0 );
  auto kreuzung4 = std::make_shared< Kreuzung >( "Kr4", 0 );

  // strabe1
  Kreuzung::vVerbinde( "W12", "W21", 40, kreuzung1, kreuzung2, Tempolimit::Innerorts, false );
  int koord1[] = { 680, 40, 680, 300 };  // 往路径坐标
  bZeichneStrasse( "W12", "W21", 40, 2, koord1 );
  // strabe2
  Kreuzung::vVerbinde( "W23a", "W32a", 115, kreuzung2, kreuzung3, Tempolimit::Unlimited, true );
  int koord2[] = { 680, 300, 850, 300, 970, 390, 970, 500, 850, 570, 680, 570 };  // 往路径坐标
  bZeichneStrasse( "W23a", "W32a", 115, 6, koord2 );
  // strabe3
  Kreuzung::vVerbinde( "W23b", "W32b", 40, kreuzung2, kreuzung3, Tempolimit::Innerorts, false );
  int koord3[] = { 680, 300, 680, 570 };  // 往路径坐标
  bZeichneStrasse( "W23b", "W32b", 40, 2, koord3 );
  // strabe4
  Kreuzung::vVerbinde( "W24", "W42", 55, kreuzung2, kreuzung4, Tempolimit::Innerorts, false );
  int koord4[] = { 680, 300, 320, 300 };  // 往路径坐标
  bZeichneStrasse( "W24", "W42", 55, 2, koord4 );
  // strabe5
  Kreuzung::vVerbinde( "W34", "W43", 85, kreuzung3, kreuzung4, Tempolimit::Unlimited, true );
  int koord5[] = { 320, 300, 320, 420, 350, 510, 500, 570, 680, 570 };  // 往路径坐标
  bZeichneStrasse( "W34", "W43", 85, 5, koord5 );
  // strabe6
  Kreuzung::vVerbinde( "W44a", "W44b", 130, kreuzung2, kreuzung3, Tempolimit::Landstrasse, true );
  int koord6[] = { 320, 300, 320, 150, 200, 60, 80, 90, 70, 250, 170, 300, 320, 300 };  // 往路径坐标
  bZeichneStrasse( "W44a", "W44b", 130, 7, koord6 );

  bZeichneKreuzung( 320, 300 );
  bZeichneKreuzung( 680, 300 );
  bZeichneKreuzung( 680, 40 );
  bZeichneKreuzung( 680, 570 );

  // 创建车辆
  std::unique_ptr< PKW >     bmw  = std::make_unique< PKW >( "BMW", 60.0, 1, 50.0 );
  std::unique_ptr< Fahrrad > trek = std::make_unique< Fahrrad >( "Trek", 25.0 );
  std::unique_ptr< PKW >     audi = std::make_unique< PKW >( "Audi", 70.0, 1, 60.0 );
  kreuzung1->vAnnahme( std::move( bmw ), 1.0 );
  kreuzung1->vAnnahme( std::move( trek ), 0.0 );
  kreuzung1->vAnnahme( std::move( audi ), 0.0 );

  // 模拟一段时间，假设总模拟时间为1小时，每次递增0.3小时
  const double zeitschritt = 0.3;
  const double simzeit     = 3;

  for ( d_GlobaleZeit = 0; d_GlobaleZeit < simzeit; d_GlobaleZeit += zeitschritt ) {
    std::cout << "当前时间: " << d_GlobaleZeit << " 小时" << std::endl;
    vSetzeZeit( d_GlobaleZeit );

    kreuzung1->vSimulieren();
    kreuzung2->vSimulieren();
    kreuzung3->vSimulieren();
    kreuzung4->vSimulieren();
    vSleep( 1000 );  // 暂停2000毫秒
  }

  // 结束图形会话
  vBeendeGrafik();
}

void vAufgabe_8() {
  const std::string filename = "../../VO.dat";
  std::ifstream     file;
  try {
    file.open( filename );
    PKW      pkw;
    Fahrrad  fahrrad;
    Kreuzung kre;

    file >> pkw;
    file >> fahrrad;
    file >> kre;
    Fahrzeug::vKopf();
    std::cout << pkw << std::endl;
    std::cout << fahrrad << std::endl;
  }
  catch ( const std::ifstream::failure& e ) {
    std::cerr << "File opeation failed" << std::endl;
  }
  catch ( const std::exception& e ) {
    std::cerr << "Exception occured!" << std::endl;
    return;
  }
}

void vAufgabe_9() {
  try {
    Simulation        sim;
    const std::string filename = "../../Simu.dat";
    std::ifstream     inputFile( filename );
    sim.vEinlesen( inputFile, true );
  }
  catch ( const std::exception& ex ) {
    std::cerr << "Catch Exception!!!!!!!" << std::endl;
  }
}

void vAufgabe_9a() {
  try {
    Simulation        sim;
    const std::string filename = "../../SimuDisplay.dat";
    std::ifstream     inputFile( filename );
    sim.vEinlesen( inputFile, true );
    sim.vSimulieren( 7, 0.3 );
  }
  catch ( const std::exception& ex ) {
    std::cerr << "Catch Exception!!!!!!!" << std::endl;
  }
}

int main() {
  vAufgabe_9a();
  std::cout << "\n=== 程序结束 ===" << std::endl;
  return 0;
}
