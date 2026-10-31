#ifndef HEADER_C504464ADB3BB822
#define HEADER_C504464ADB3BB822

# pragma once
#include <iostream>
# include <cstdint>
#include <string>
#include "Memory.h"

enum RocketState : uint8_t {    //zmienna stanu rakiety
    DISARM = 0 ,
    ARM = 1 ,
    FLIGHT = 2 ,
    PARACHUTE = 3 ,
    LANDED = 4
};


class TelemetryBlackBox {   //klasa blackboxa
private:
    std::uint16_t altitude = 0;     //zmienna wysokosci
    std::uint32_t frame = 0;        //zmienna ramki zapisywanej w buforze
    bool parachuteDeployed = false, baroError = false;      //zmienne logiczne odpowiadajace wypuszczeniu spadochronu i bledowi barometru
    int stateValue = 0;     //zmienna zamieniajaca stan rakiety na integer

    Memory memory;      //element klasy memory - bufor kolowy

public :
    std::string onString(RocketState state);        //funkcja rzutujaca stan rakiety na stringa, wywolywana podczas dekodowania ramki

    void onRocketStateChange ( RocketState state ) ;    //funkcja ustalajaca stan rakiety

    void onParachuteDeployed () ;   //funkcja odpowiedzialna za wypuszczenie spadochronu

    void onBaroReading ( bool error , uint16_t value ) ;        //funkcja odczytujaca wskazania barometru

    void recordCurrentState () ;        //funkcja skladajaca ramke i wysylajaca ja do bufora

    void memoryShow();      //funkcja wypisujaca caly bufor

    std::uint32_t getLastDataframe () ;     //funkcja dekodujaca ostatnia zapisana ramke i sprawdzajaca zgodnosc sumy kontrolnej

    std::uint32_t getMemoryElement (int index);     //funkcja zwracajaca wybrany element bufora

    void checksumChange (int index) ;   //funkcja zmieniajaca sume kontrolna wybranej ramki, sluzaca do przeprowadzenia testu (dziala tylko dla wybranych przypadkow)
};

#endif // header guard 

