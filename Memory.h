#pragma once

class Memory{   //Klasa bufora kolowego
    private:

    std::uint32_t memoryArray[16] = {}; //tablica bufora
    int memoryIndex = 0;    //indeks bufora

    public:

    void save (uint32_t memoryFrame);   //funkcja zapisujaca element do bufora
    void show ();   //funkcja pokazujaca tablice bufora
    std::uint32_t read();   //funkcja odczytujaca ostatni zapisany element bufora

    bool bufferRecordCheck();   //funkcja sprawdzajaca, czy w buforze sa juz zapisane jakies elementy

    std::uint32_t getElement(int index);    //funkcja zwracajaca wybrany element bufora

    void wrongChecksum (int index);     /*funkcja zmienajaca wartosc sumy kontrolnej w ramce, sluzaca do przeprowadzenia odpowiedniego testu
    (dziala tylko dla niektorych przypadkow) */
};