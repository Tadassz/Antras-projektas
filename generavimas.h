
#ifndef GENERAVIMAS_H
#define GENERAVIMAS_H

#include <random>

// klase atsitiktiniams skaiciams
class AtsitiktinisSk{
    private:
        std::random_device rd;
        std::mt19937 mt;
    public:
        AtsitiktinisSk();
        int Skaicius(int pradzia, int pabaiga);
};

#endif
