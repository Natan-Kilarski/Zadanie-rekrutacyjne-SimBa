#include <iostream>
#include <cstdint>
#include <bitset>
#include "TelemetryBlackBox.h"
#include "Memory.h"

void testBufferReadBeforeRecorded() {       //test sprawdzajacy odczyt bufora, do ktorego nie trafila jeszcze zadna ramka
    TelemetryBlackBox box = TelemetryBlackBox();
    std::uint32_t returnValue = box.getLastDataframe();
    if (returnValue == 0x0FFFFFF0) {
        std::cout << "Correct program response - no frame recorded, error occurred" << std::endl;
        std::cout << "Error code: " << std::hex << returnValue << std::endl;
    }

    else {
        std::cout << "Incorrect program response - no frame recorded, no error occurred" << std::endl;
    }
}

void testBufferReadClassic() {      //test sprawdzajacy odczyt standardowej ramki
    TelemetryBlackBox box = TelemetryBlackBox();
    box.onRocketStateChange(FLIGHT);
    box.onBaroReading(false, 54321);
    box.recordCurrentState();
    std::cout << "0b" << std::bitset<32>(box.getMemoryElement(0)) << std::endl;
    std::uint32_t returnValue = box.getLastDataframe();
    if (returnValue == 0b11100111110101000011000100000010) {
        std::cout << "Correct program response" << std::endl;
    }

    else {
        std::cout << "Incorrect program response - recorded frame doesn't match target value" << std::endl;
    }
}

void testBufferReadOnParachuteDeployed() {      //test sprawdzajacy ramke po wypuszczeniu spadochronu
    TelemetryBlackBox box = TelemetryBlackBox();
    box.onBaroReading(false, 2314);
    box.onRocketStateChange(PARACHUTE);
    box.onParachuteDeployed();
    box.recordCurrentState();
    std::cout << "0b" << std::bitset<32>(box.getMemoryElement(0)) << std::endl;
    std::uint32_t returnValue = box.getLastDataframe();
    if (returnValue == 0b00001000000010010000101000001011) {
        std::cout << "Correct program response" << std::endl;
    }

    else {
        std::cout << "Incorrect program response - recorded frame doesn't match target value" << std::endl;
    }
}

void CircularBufferTest() {     //test sprawdzajacy, czy elementy bufora kolowego odpowiednio sie nadpisuja
    TelemetryBlackBox box = TelemetryBlackBox();
    for (int i = 0; i < 16; i++) {
        box.onBaroReading(false, 2314);
        box.onRocketStateChange(PARACHUTE);
        box.onParachuteDeployed();
        box.recordCurrentState();
    }
    box.onRocketStateChange(FLIGHT);
    box.onBaroReading(false, 54321);
    box.recordCurrentState();
    box.getLastDataframe();
    box.memoryShow();

    std::uint32_t returnValue = box.getMemoryElement(0);

    if (returnValue == 0b11101111110101000011000100001010) {
        std::cout << "Correct program response" << std::endl;
    }

    else {
        std::cout << "Incorrect program response - recorded frame doesn't match target value" << std::endl;
    }
}

void testBufferReadOnBaroError() {      //test sprawdzajacy odczyt ramki po bledzie barometru
    TelemetryBlackBox box = TelemetryBlackBox();
    box.onBaroReading(true, 23000);
    box.onRocketStateChange(ARM);
    box.recordCurrentState();
    std::cout << "0b" << std::bitset<32>(box.getMemoryElement(0)) << std::endl;
    std::uint32_t returnValue = box.getLastDataframe();

    if (returnValue == 0b00010001111111111111111100010001) {
        std::cout << "Correct program response" << std::endl;
    }

    else {
        std::cout << "Incorrect program response - recorded frame doesn't match target value" << std::endl;
    }

}

void testBufferReadOnLanded() {     //test sprawdzajacy odczyt ramki po wyladowaniu
    TelemetryBlackBox box = TelemetryBlackBox();
    box.onBaroReading(false, 12345);
    box.onRocketStateChange(LANDED);
    box.recordCurrentState();
    std::cout << "0b" << std::bitset<32>(box.getMemoryElement(0)) << std::endl;
    std::uint32_t returnValue = box.getLastDataframe();
    if (returnValue == 0b00000100000000000000000000000100) {
        std::cout << "Correct program response" << std::endl;
    }

    else {
        std::cout << "Incorrect program response - recorded frame doesn't match target value" << std::endl;
    }

}

void testBufferReadOnWrongChecksumValue() {     //test sprawdzajacy odczyt ramki z nieprawidlowa suma kontrolna
    TelemetryBlackBox box = TelemetryBlackBox();
    box.onBaroReading(false, 12345);
    box.onRocketStateChange(LANDED);
    box.recordCurrentState();
    box.checksumChange(0);
    std::cout << "0b" << std::bitset<32>(box.getMemoryElement(0)) << std::endl;
    std::uint32_t returnValue = box.getLastDataframe();

    if (returnValue == 0xFFFFFFFF) {
        std::cout << "Correct program response" << std::endl;
        std::cout << "Error code: " << std::hex << returnValue << std::endl;
    }

    else {
        std::cout << "Incorrect program response - checksum incorrect, no error occurred" << std::endl;
    }
}

int main() {
    std::cout << "Test odczytu bufora bez zadnej zapisanej ramki:" << std::endl;
    testBufferReadBeforeRecorded();
    std::cout << "Test odczytu klasycznej ramki z bufora (bez zadnych bledow):" << std::endl;
    testBufferReadClassic();
    std::cout << "Test odczytu ramki z bledem barometru:" << std::endl;
    testBufferReadOnBaroError();
    std::cout << "Test odczytu ramki po wyladowaniu rakiety:" << std::endl;
    testBufferReadOnLanded();
    std::cout << "Test odczytu ramki po wypuszczeniu spadochronu:" << std::endl;
    testBufferReadOnParachuteDeployed();
    std::cout << "Test prawidlowego nadpisywania elementow w buforze kolowym:" << std::endl;
    CircularBufferTest();
    std::cout << "Test odczytu ramki z nieprawidlowa suma kontrolna:" << std::endl;
    testBufferReadOnWrongChecksumValue();

    return 0;
}
