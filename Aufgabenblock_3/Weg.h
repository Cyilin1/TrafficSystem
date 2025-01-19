#ifndef WEG_H
#define WEG_H

#include "Simulationsobjekt.h"
#include "vertagt_liste.h"
#include <iostream>
#include <limits> // For std::numeric_limits
#include <list>
#include <memory> // For smart pointers

class Fahrzeug;
class Kreuzung;

enum class Tempolimit {
  Unlimited,   // 无速度限制
  Landstrasse, // 乡村道路，限速 100 km/h
  Innerorts    // 市区道路，限速 50 km/h
};

class Weg : public Simulationsobjekt {
private:
    double                                         p_dLaenge;       // 路径长度
    std::shared_ptr< Kreuzung >                    pStartKreuzung;  // 起点十字路口（共享指针）
    const std::weak_ptr< Kreuzung >                pEndKreuzung;    // 目标十字路口（弱引用）
    std::weak_ptr< Weg >                           pOppositeWeg;    // 对应的返程路段
    Tempolimit                                     p_eTempolimit;   // 速度限制
    vertagt::VListe< std::unique_ptr< Fahrzeug > > p_pFahrzeuge;
    bool                                           bUeberholverbot;  // 超车禁令

public:
    Weg();
    // 带名称、长度和可选速度限制的构造函数
    Weg( const std::string& name, double laenge, Tempolimit tempolimit = Tempolimit::Unlimited, bool ueberholverbot = false );

    Weg( const std::string& name, double laenge, std::shared_ptr< Kreuzung > pStart, Tempolimit tempolimit = Tempolimit::Unlimited, bool ueberholverbot = false );
    Weg( const std::string& name, double laenge, std::shared_ptr< Kreuzung > pStart, std::shared_ptr< Kreuzung > pEnd, Tempolimit tempolimit = Tempolimit::Unlimited, bool ueberholverbot = false );

    void setOppositeWeg( std::weak_ptr< Weg > oppositeWeg ) {
        pOppositeWeg = std::move( oppositeWeg );
    }
    void vAnnahme( std::unique_ptr< Fahrzeug > pFzg );
    // 重载函数，接纳停放的车辆
    void                        vAnnahme( std::unique_ptr< Fahrzeug > pFahrzeug, double dStartzeit );
    std::unique_ptr< Fahrzeug > pAbgabe( const Fahrzeug& fahrzeug );
    // 模拟方法
    virtual void vSimulieren() override;

    // 输出方法
    static void  vKopf();
    virtual void vAusgeben( std::ostream& os ) const;
    virtual void         vAusgeben() const override;
    friend std::ostream& operator<<( std::ostream& os, const Weg& fahrzeug ) {
        fahrzeug.vAusgeben( os );
        return os;
    }

    // 获取指定车辆虚拟障碍的位置
    double getBarriere( const Fahrzeug& faz );

    // ==========================GETTER=======================
    std::shared_ptr< Weg > getOppositeWeg() const {
        return pOppositeWeg.lock();
    }
    std::shared_ptr< Kreuzung > getEndKreuzung() const {
        return pEndKreuzung.lock();
    }
    double getTempolimit() const {
        return static_cast< double >( p_eTempolimit ); }
  double getLaenge() const {
      return p_dLaenge;
  }
  double getUeberholverbot() const {
      return bUeberholverbot;
  }
  double dGetTempolimit() const;

  const vertagt::VListe<std::unique_ptr<Fahrzeug>> &getFahrzeuge() const {
    return p_pFahrzeuge;
  }
};

#endif // WEG_H
