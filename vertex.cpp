#include <list>
#include <algorithm>

#include "vertex.h"
#include "edge.h"

Vertex::Vertex(Station& _station){
    station = &_station;
}

bool Vertex::AddEdge(Edge& newEdge){
    //check if the neighbor inside the new edge is already there in the list of edges, if so return false
    std::list<Edge*>::iterator iter = std::find(edges.begin(), edges.end(), &newEdge);
    if (iter != edges.end())
    {
        std::cout << "Duplicate edge" << std::endl;
        return false;
    }

    //otherwise add the edge and return true
    edges.push_back(&newEdge);
    return true;
}

void Vertex::Print(){
    station->PrintStationName();
    std::cout <<" - "<< std::endl;
    for (Edge* e : edges)
    {
        std::cout <<"    ";
        e->GetNeighbor()->GetStation()->PrintStationName();
        std::cout << " on " << e->GetLine() << "(" << e->GetDirection() << ") taking " << e->GetTime() << " mins.";
        if (e->IsOpen() && e->GetDelay() > 0) { std::cout << " " << e->GetDelay() << " mins delay"; }
        if (!e->IsOpen()) { std::cout << "This route is closed."; }
        std::cout << std::endl;
    }
}