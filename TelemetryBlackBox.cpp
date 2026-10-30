#include <iostream>
#include <cstdint>
#include <string>
#include "TelemetryBlackBox.h"

std::uint8_t byte0 = 0, byte1 = 0, byte2 = 0, checksum = 0;
std::uint16_t altitude = 0;
std::uint32_t frame = 0;
bool parachuteDeployed = false, baroError = false;
RocketState state = DISARM;

std::string onString (RocketState state){
    switch (state){
        case RocketState::DISARM:
        return "DISARM";

        case RocketState::ARM:
        return "ARM";

        case RocketState::FLIGHT:
        return "FLIGHT";

        case RocketState::PARACHUTE:
        return "PARACHUTE";

        case RocketState::LANDED:
        return "LANDED";

        default:
        return "WRONG ROCKET STATE";
    }
}

void TelemetryBlackBox::onRocketStateChange (RocketState state){
    byte0 = state;
}

void TelemetryBlackBox::onParachuteDeployed(){
    parachuteDeployed = true;
}

void TelemetryBlackBox::onBaroReading(bool error, std::uint16_t value){
    baroError = error;
    altitude = value;
}

void TelemetryBlackBox::recordCurrentState(){
    if (parachuteDeployed == true){
        byte0 = byte0 | (1 << 3);
    }

    if (baroError == true){
        byte0 = byte0 | (1 << 4);
        altitude = 0b1111111111111111;
    }

    if ((state == 0) || (state == 4)){
        altitude = 0;
    }

    byte1 = static_cast<std::uint8_t>(altitude & 0b0000000011111111);
    byte2 = static_cast<std::uint8_t>((altitude & 0b1111111100000000) >> 8);

    checksum = byte0 ^ byte1 ^ byte2;

    frame = static_cast<std::uint32_t>(checksum << 24) + static_cast<std::uint32_t>(byte2 << 16) + static_cast<std::uint32_t>(byte1 << 8) + static_cast<std::uint32_t>(byte0);

    memory.save(frame);
}

uint32_t getLastDataframe(){
    


}
