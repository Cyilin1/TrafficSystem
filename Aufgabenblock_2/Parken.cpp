#include "Parken.h"
#include "Fahren.h"
#include "Fahrzeug.h"
#include "Fahrzeugausnahme.h"
const double epsilon = 1e-6;

double ParkingBehavior::calculateDistance( Vehicle& vehicle, double timeInterval ) {
    if ( globalTime < m_startTime && std::fabs( globalTime - m_startTime ) >= epsilon ) {
        std::cout << "Fahrzeug " << vehicle.getName() << " 停放中，启动时间未到达。" << std::endl;
        return 0.0;
    }

    /**
     * 这里设计的逻辑是：
     * 1. 到达启动时间：把当前时间设置一下，然后throw启动异常；
     */
    if ( !bGestartet ) {
        std::cout << "Fahrzeug " << vehicle.getName() << " 启动了，开始行驶。" << std::endl;
        bGestartet = true;
        vehicle.setTime( m_startTime );
        throw StartException( vehicle, TravelBehavior::getWeg() );
    }

    return TravelBehavior::calculateDistance( vehicle, timeInterval );
}
