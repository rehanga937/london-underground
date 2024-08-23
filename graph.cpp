#include <iostream>
#include <list>

#include "graph.h"

Vertex* Graph::getClosestUnvisistedVertex(){
    float min = 1000000;
    Vertex* closestUnvisitedVertex = nullptr;
    for (Vertex* v : priorityQueue){
        if (!v->IsVisited && v->ShortestDistance < min){
            min = v->ShortestDistance;
            closestUnvisitedVertex = v;
        }
    }
    return closestUnvisitedVertex;
}

Vertex* Graph::GetVertexByName(std::string name){
    for (Vertex* vertex : vertices){
        if (vertex->GetStation()->GetName() == name){
            return vertex;
        }
    }
    std::cout << name << " station does not exist in graph." << std::endl;
    return nullptr;
}

bool Graph::AddVertex(Vertex& newVertex){
    //check if the vertex already exists in the graph, if so return false
    for (Vertex* vertex : vertices){
        if (vertex == &newVertex){
            std::cout << "Vertex already exists in the graph" << std::endl;
            return false;
        }
        if (vertex->GetStation()->GetName() == newVertex.GetStation()->GetName()){
            std::cout << "Vertex already exists in the graph" << std::endl;
            return false;
        }        
    }
    vertices.push_back(&newVertex);
    return true;
}

void Graph::Print(){
    for (Vertex* vertex : vertices){
        vertex->Print();
        std::cout << std::endl;
    }
}

void Graph::DijkstraShortestPathAlgorithm(Vertex& startVertex, Vertex& endVertex){
    //initializing for Dijkstra
    priorityQueue.clear();
    priorityQueue.push_front(&startVertex);
    for (Vertex* vertex : vertices)
    {
        vertex->PreviousVertex = nullptr;
        vertex->IsVisited = false;
        if (vertex == &startVertex) { vertex->ShortestDistance = 0; }
        else { vertex->ShortestDistance = 1000000; }
    }

    //algorithm
    while (!endVertex.IsVisited)//(while end vertex is unvisited)
    {
        //get the closes univisted vertex
        Vertex* closestUnvisitedVertex = Graph::getClosestUnvisistedVertex();

        //get its (shortest) distance from start
        float distanceFromStart = closestUnvisitedVertex->ShortestDistance;

        //get edges from the selected vertex
        std::list<Edge*> edges = closestUnvisitedVertex->GetEdges();

        //for each unvisited neighbor, distance from start vertex is calculated, and the Dijkistra properties are updated with the distance and previous vertex if it's shorter
        for (Edge* edge : edges)
        {
            if (edge->GetNeighbor()->IsVisited || !edge->IsOpen()) { continue; }
            Vertex* neighbor = edge->GetNeighbor();
            float itsWeight = edge->GetWeight();
            itsWeight += distanceFromStart;
            if (neighbor->ShortestDistance > itsWeight)
            {
                neighbor->ShortestDistance = itsWeight;
                neighbor->PreviousVertex = closestUnvisitedVertex;
                neighbor->PreviousEdge = edge;
                priorityQueue.push_back(neighbor);
            }
        }

        //closestUnvisitedVertex is now visited
        closestUnvisitedVertex->IsVisited = true;
        priorityQueue.remove(closestUnvisitedVertex);
    }
}
