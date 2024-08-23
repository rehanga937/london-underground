#ifndef STATION
#define STATION

#include <string>
#include <iostream>

class Station{
    private:

        std::string name;

    public:

        Station(std::string _name){ name = _name; }

        std::string GetName(){ return name; }
        
        void PrintStationName() { std::cout << name; }
};

#endif