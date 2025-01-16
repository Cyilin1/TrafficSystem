#ifndef KREUZUNG_H
#define KREUZUNG_H
#include "Simulationsobjekt.h"
#include "Weg.h"

class Kreuzung : public Simulationsobjekt {
public:
    Kreuzung( const std::string& sName = "", double dTankstelle = 0.0 );

    virtual void vEinlesen( std::istream& is );
    /**
     * @brief vVerbinde 函数作用是将两个十字路口和两个Weg（去程和返程）Bind一起
     * @param sNameHin
     * @param sNameRueck
     * @param dLaenge
     * @param pStartKreuzung
     * @param pEndKreuzung
     * @param eTempolimit
     * @param bUeberholverbot
     */
    static void vVerbinde( const std::string& sNameHin, const std::string& sNameRueck, double dLaenge, std::shared_ptr< Kreuzung > pStartKreuzung, std::shared_ptr< Kreuzung > pEndKreuzung,
                           Tempolimit eTempolimit, bool bUeberholverbot );
    double dTanken( Fahrzeug& fzg );

    void vSimulieren();
    /**
     * @brief vAnnahme 添加Weg到当前的十字路口
     * @param pWeg
     */
    void vAnnahme( std::shared_ptr< Weg > pWeg );
    void vAnnahme( std::unique_ptr< Fahrzeug > fahrzeug, double dStartzeit );

    /**
     * @brief 在转移车辆时，应从十字路口发出的路段中随机选择一个。
     * 但车辆不应返回其来时的路段。
     * 为此，实现一个函数 shared_ptr<Weg> Kreuzung::pZufaelligerWeg(Weg&)，
     * @param einfahrWeg 表示车辆进入十字路口的路段的引用
     * @return 返回值是为车辆选择的路段。如果是“死胡同”，则必须选择返程路段。
     */
    std::shared_ptr< Weg > pZufaelligerWeg( Weg& einfahrWeg );
    double                 getRemainingFuel() {
        return pdTankstelle;
    }

private:
    std::list< std::shared_ptr< Weg > > p_Weg;  // 存储从该十字路口“发出”的所有道路
    // 十字路口占有某个Weg对象，而这个Weg对象同时地被它对面的Weg对象占有
    double pdTankstelle;
};

#endif // KREUZUNG_H
