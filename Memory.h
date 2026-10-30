#pragma once

class Memory{
    private:

    std::uint32_t memoryArray[16] = {};
    int memoryIndex = 0;

    public:

    void save (uint32_t memoryFrame);
    void show ();
    std::uint32_t read();
};