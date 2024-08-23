#ifndef EDGE
#define EDGE

#include <string>

#include "vertex.h"

class Vertex;

class Edge{
    private:

        Vertex* neighbor;
        float time;
        float delay;
        std::string line;
        std::string direction;
        bool open;

    public:

        Edge(Vertex*,float,std::string,std::string);

        Vertex* GetNeighbor () { return neighbor;}
        float GetTime () { return time; }
        float GetDelay () { return delay; }
        float GetWeight() { return (time + delay); }
        std::string GetLine () { return line; }
        std::string GetDirection () { return direction; }
        bool IsOpen() { return open; }

        void SetDelay(float _delay) { delay = _delay; }
        void OpenEdge() { open = true; }
        void CloseEdge() { open = false; }

        void Print();
};

#endif