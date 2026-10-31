#include <iostream>
#include <cstdint>
#include <bitset>
#include "Memory.h"


void Memory::save (std::uint32_t memoryFrame){
    memoryArray[memoryIndex] = memoryFrame;
    memoryIndex = (memoryIndex + 1) % 16;
}

void Memory::show(){
    std::cout << "Memory:" << std::endl;
    for (int i = 0; i < 16; i++){
        std::cout << "0b" << std::bitset<32>(memoryArray[i]) << std::endl;
    }
}

std::uint32_t Memory::read(){
    return memoryArray[(memoryIndex + 15) % 16];
}

bool Memory::bufferRecordCheck() {
    for (int j = 0; j < 16; j++) {
        if (memoryArray[j] != 0) {
            return false;
        }

        else {
            return true;
        }
    }
}

std::uint32_t Memory::getElement (int index){
    return memoryArray[index];
}

void Memory::wrongChecksum (int index) {
    if (index >= 0 && index < 16) {
        memoryArray[index] |= (1 << 31);
    }
}
