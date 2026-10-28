#ifndef HEADER_C504464ADB3BB822
#define HEADER_C504464ADB3BB822

# pragma once
# include < cstdint >

enum RocketState : uint8_t {
    DISARM = 0 ,
    ARM = 1 ,
    FLIGHT = 2 ,
    PARACHUTE = 3 ,
    LANDED = 4
};


class TelemetryBlackBox {
public :
    void onRocketStateChange ( RocketState state ) ;
    void onParachuteDeployed () ;

    /**
    * @param error - Informuje czy wyst ¹pi³ b³¹d barometru
    * @param value - Odczyt wysoko œci w stopach
    */
    void onBaroReading ( bool error , uint16_t value ) ;

    /**
    * @brief Pobiera bie¿¹cy stan , sk³ada go w 32 - bitow ¹ ramk ê z sum¹ kontroln ¹
    i zapisuje do bufora .
    */
    void recordCurrentState () ;

    /**
    * @brief Funkcja pobiera ostatni ¹ ramk ê z bufora ko³owego , dekoduje j¹ oraz
    loguje zdekodowane warto œci w czytelny spos ób na konsol ê.
    * @Return Ostatnia ramka zapisana do bufora , jeœli xor siê zgadza .
    0 xFFFFFFFF jeœli suma kontrolna jest niepoprawna .
    */
    uint32_t getLastDataframe () ;
};

#endif // header guard 

