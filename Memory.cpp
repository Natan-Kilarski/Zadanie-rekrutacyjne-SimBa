#include <iostream>
#include <cstdint>
#include "Memory.h"

std::uint16_t memory[16] = {};
int memory_index = 0;

void Memory::save (std::uint32_t memoryFrame){
    memory[memory_index] = memoryFrame;
    memory_index = (memory_index + 1) % 16;
}

void Memory::show(){
    std::cout << "Memory:" << std::endl;
    for (int i = 0; i < 16; i++){
        std::cout << memory[i] << std::endl;
    }
}

