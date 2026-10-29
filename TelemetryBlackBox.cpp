#include <iostream>
#include <cstdint>
#indlude "TelemetryBlackBox.h"

void TelemetryBlackBox::onRocketStateChange (Rocketstate State){
    if (State == 3){
        std::uint8_t TemporaryState = State | (1 << 3);
    }
}
void TelemetryBlackBox::onParachuteDeployed(){
    
}

    bool error;
    std::uint16_t value;

void TelemetryBlackBox::onBaroReading(bool error, uint16_t value){
    if (error == true){
        TemporaryState = State | (1 << 4);
        value = 0b11111111;
    }

    if ((RocketState State == 0) || (RocketState State == 4)){
        value = 0b00000000;
    }
}

void TelemetryBlackBox::recordCurrentState(){
    std::uint8_t Byte2 = (value & 0b1111111100000000) >> 8;
    
    std::uint8_t Byte1 = value & 0b0000000011111111;
    
    std::uint8_t Byte0 = TemporaryState;
    
    std::uint8_t Checksum = (Byte0 ^ Byte1 ^ Byte2);

    std::uint32_t frame = (checksum << 24) + (Byte2 << 16) + (Byte1 << 8) + Byte0;

    Memory::save(frame);

}

uint32_t getLastDataframe(){

}