#ifndef GRAPH
#define GRAPH

#include <list>
#include <string>

#include "vertex.h"

class Graph{
    private:

        std::list<Vertex*> vertices;

        /*non-core attributes. Used for Dijkstra's algorithm*/
        std::list<Vertex*> priorityQueue;
        
        Vertex* getClosestUnvisistedVertex();//helper function for DijkstraShortestPathAlgorithm function

    public:

        Graph(){};

        Vertex* GetVertexByName(std::string);//returns vertex of a particular station name
        std::list<Vertex*> GetVertices() { return vertices; }

        bool AddVertex(Vertex&);

        void Print();
        void DijkstraShortestPathAlgorithm(Vertex&,Vertex&);//performs Dijkstra's shortest path algorithm (updating the relevant attributes of the nodes in the graph)

};

#endif