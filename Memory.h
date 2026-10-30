#include <iostream>

#pragma once

class Memory{
    private:

    std::uint32_t memoryArray[16] = {};
    int memoryIndex;

    public:

    void save (uint32_t memoryFrame);
    void show ();
    std::uint32_t read();
};