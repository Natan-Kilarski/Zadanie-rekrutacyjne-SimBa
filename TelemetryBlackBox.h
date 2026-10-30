#ifndef HEADER_C504464ADB3BB822
#define HEADER_C504464ADB3BB822

# pragma once
#include <iostream>
# include <cstdint>
#include <string>
#include "Memory.h"

enum RocketState : uint8_t {
    DISARM = 0 ,
    ARM = 1 ,
    FLIGHT = 2 ,
    PARACHUTE = 3 ,
    LANDED = 4
};


class TelemetryBlackBox {
private:
    std::uint8_t  byte0Check, byte1Check, byte2Check, checksumCheck;
    std::uint16_t altitude;
    std::uint32_t frame;
    bool parachuteDeployed, baroError;
    int stateValue;

    Memory memory;

public :
    std::string onString(RocketState state);

    void onRocketStateChange ( RocketState state ) ;

    void onParachuteDeployed () ;

    /**
    * @param error - Informuje czy wyst �pi� b��d barometru
    * @param value - Odczyt wysoko �ci w stopach
    */

    void onBaroReading ( bool error , uint16_t value ) ;

    /**
    * @brief Pobiera bie��cy stan , sk�ada go w 32 - bitow � ramk � z sum� kontroln �
    i zapisuje do bufora .
    */
    void recordCurrentState () ;

    /**
    * @brief Funkcja pobiera ostatni � ramk � z bufora ko�owego , dekoduje j� oraz
    loguje zdekodowane warto �ci w czytelny spos �b na konsol �.
    * @Return Ostatnia ramka zapisana do bufora , je�li xor si� zgadza .
    0 xFFFFFFFF je�li suma kontrolna jest niepoprawna .
    */
    uint32_t getLastDataframe () ;
};

#endif // header guard 

