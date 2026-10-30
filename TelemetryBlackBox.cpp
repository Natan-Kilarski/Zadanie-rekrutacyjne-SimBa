#include <iostream>
#include <cstdint>
#include <string>
#include <bitset>
#include "TelemetryBlackBox.h"

std::uint8_t byte0 = 0, byte1 = 0, byte2 = 0, checksum = 0, byte0Check = 0, byte1Check = 0, byte2Check = 0, checksumCheck = 0;
std::uint16_t altitude = 0;
std::uint32_t frame = 0;
bool parachuteDeployed = false, baroError = false;
RocketState state = DISARM;

std::string TelemetryBlackBox::onString (RocketState state){
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
    byte0 = (byte0 & 0b11111000) | state;
    std::cout << byte0 << std::endl;
}

void TelemetryBlackBox::onParachuteDeployed(){
    parachuteDeployed = true;
}

void TelemetryBlackBox::onBaroReading(bool error, std::uint16_t value){
    baroError = error;
    altitude = value;
    std::cout << baroError << std::endl;
    std::cout << altitude << std::endl;
}

void TelemetryBlackBox::recordCurrentState(){
    if (parachuteDeployed == true){
        byte0 = byte0 | (1 << 3);
        std::cout << byte0 << std::endl;
    }

    if ((state == 0) || (state == 4)){
        altitude = 0;
        std::cout << altitude << std::endl;
    }

    if (baroError == true){
        byte0 = byte0 | (1 << 4);
        altitude = 0b1111111111111111;
        std::cout << byte0 << std::endl;
        std::cout << altitude << std::endl;
    }

    else {
        byte0 = byte0 & ~(1 << 4);
        std::cout << byte0 << std::endl;
    }

    

    byte1 = static_cast<std::uint8_t>(altitude & 0x0000FFFF);
    byte2 = static_cast<std::uint8_t>((altitude & 0x00FFFF00) >> 8);

    std::cout << byte1 << std::endl;
    std::cout << byte2 << std::endl;

    checksum = byte0 ^ byte1 ^ byte2;

    std::cout << checksum << std::endl;

    frame = (static_cast<std::uint32_t>(checksum) << 24) + (static_cast<std::uint32_t>(byte2) << 16) 
    + (static_cast<std::uint32_t>(byte1) << 8) + static_cast<std::uint32_t>(byte0);

    memory.save(frame);

    memory.show();
}

std::uint32_t TelemetryBlackBox::getLastDataframe(){
    
    std::uint32_t lastFrame = memory.read();

    std::cout << "Stan rakiety - " << onString(static_cast<RocketState>(lastFrame & 0x00000007)) << std::endl;

    if ((lastFrame & 0b0000000000000000000000000001000) != 0){
        std::cout << "Parachute deployed" << std::endl;
    }

    else {
        std::cout << "Parachute not deployed" << std::endl;
    }

    if ((lastFrame & 0b00000000000000000000000000010000) == 0){
        std::cout << "Correct barometer reading" << std::endl;
    }

    else {
        std::cout << "Barometer error" << std::endl;
    }

    std::cout << "Altitude = " << ((lastFrame & 0x00FFFF00) >> 8) << std::endl;

    byte0Check = static_cast<std::uint8_t>(lastFrame & 0x000000FF);
    byte1Check = static_cast<std::uint8_t>((lastFrame & 0x0000FF00) >> 8);
    byte2Check = static_cast<std::uint8_t>((lastFrame & 0x00FF0000) >> 16);

    checksumCheck = byte0Check ^ byte1Check ^ byte2Check;

    

    if (checksumCheck == checksum){
        std::cout << "Checksum correct" << std::endl;
        return lastFrame;
    }

    else {
        std::cout << "Checksum incorrect" << std::endl;
        return 0xFFFFFFFF;
    }



}
