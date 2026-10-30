#include <iostream>
#include <cstdint>
#include <string>
#include <bitset>
#include "TelemetryBlackBox.h"



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
    stateValue = state;

}

void TelemetryBlackBox::onParachuteDeployed(){
    parachuteDeployed = true;
}

void TelemetryBlackBox::onBaroReading(bool error, std::uint16_t value){
    baroError = error;
    altitude = value;
    std::cout << baroError << "baroerror" << std::endl;
    std::cout << altitude << "altitude" << std::endl;
}

void TelemetryBlackBox::recordCurrentState(){

    uint8_t byte0, byte1, byte2, checksum;

    if (parachuteDeployed == true){
        byte0 = byte0 | (1 << 3);
        std::cout << byte0 << "b0" << std::endl;
    }

    if (stateValue == 0 or stateValue == 4){
        altitude = 0;
        std::cout << state << "state" << std::endl;
        std::cout << altitude << "alt" << std::endl;
    }

    if (baroError == true){
        byte0 = byte0 | (1 << 4);
        altitude = 0b1111111111111111;
        std::cout << byte0 << "byte0" << std::endl;
        std::cout << altitude << "znowu alt" << std::endl;
    }

    else {
        byte0 = byte0 & ~(1 << 4);
        std::cout << byte0 << "znowu b0" << std::endl;
    }



    byte0 = (byte0 & 0b11111000) | state;
    std::cout << std::bitset<3>(byte0) << " Rocket state" << std::endl;

    byte1 = static_cast<std::uint8_t>(altitude & 0x00FF);
    byte2 = static_cast<std::uint8_t>((altitude & 0xFF00) >> 8);

    std::cout << std::bitset<8>(byte1) << "bitset b1" << std::endl;
    std::cout << std::bitset<8>(byte2) << "bitset b2" << std::endl;

    checksum = byte0 ^ byte1 ^ byte2;

    std::cout << checksum << "checksum" << std::endl;

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
