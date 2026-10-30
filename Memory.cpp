#include <iostream>
#include <cstdint>
#include "Memory.h"

std::uint32_t memory[16] = {};
int memoryIndex = 0;

void Memory::save (std::uint32_t memoryFrame){
    memory[memoryIndex] = memoryFrame;
    memoryIndex = (memoryIndex + 1) % 16;
}

void Memory::show(){
    std::cout << "Memory:" << std::endl;
    for (int i = 0; i < 16; i++){
        std::cout << memory[i] << std::endl;
    }
}

