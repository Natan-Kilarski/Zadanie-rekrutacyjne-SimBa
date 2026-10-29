#include <iostream>

#pragma once

class Memory{
    private:

    uint32_t memory[16];
    int memory_index;

    public:

    void save (uint32_t memoryFrame);
    void show ();




}