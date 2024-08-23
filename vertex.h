#ifndef VERTEX
#define VERTEX

#include <list>

#include "station.h"
#include "edge.h"

class Edge;

class Vertex{
    private:

        Station* station;
        std::list<Edge*> edges;

    public:

        /*non-core attributes. Used for Dijkstra's algorithm*/
        Vertex* PreviousVertex;
        Edge* PreviousEdge;
        float ShortestDistance;
        bool IsVisited;

        Vertex(Station&);

        Station* GetStation() { return station; }
        std::list<Edge*> GetEdges() { return edges;}

        void SetStation(Station& _station) { station = &_station; }
        bool AddEdge(Edge&);

        void Print();
};

#endif