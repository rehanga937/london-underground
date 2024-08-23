#include <string>
#include <iostream>
#include <chrono>
#include <list>
#include <iomanip> //used for std::setprecision

#include "funcsForMenu.h"

std::list<Edge*> funcsForMenu::GetDirectionEdges(Graph& graph, std::string& station1, std::string& station2){
    Vertex* vertex1 = graph.GetVertexByName(station1);
    Vertex* vertex2 = graph.GetVertexByName(station2);

    // Stopwatch start to time Dijkstra's Algorithm
    //long ticksPerSecond = std::chrono::high_resolution_clock::period::den;
    //long nanosecondsPerTick = (1000L * 1000L * 1000L)/nanosecondsPerTick;
    std::chrono::time_point<std::chrono::high_resolution_clock> startTime = std::chrono::high_resolution_clock::now();

    graph.DijkstraShortestPathAlgorithm(*vertex1, *vertex2);

    // Stopwatch stop to time Dijkstra's Algorithm
    std::chrono::time_point<std::chrono::high_resolution_clock> endTime = std::chrono::high_resolution_clock::now();
    std::cout << "Dijkstra's Algorithm Time (ns) " << std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime).count() << std::endl;

    std::list<Edge*> edges;

    while (vertex1 != vertex2) {
        edges.push_back(vertex2->PreviousEdge);
        vertex2 = vertex2->PreviousVertex;
    }

    return edges;
}

bool funcsForMenu::IsStationValid(Graph& graph, std::string& name){
    for (Vertex* v : graph.GetVertices()){
        if (name == v->GetStation()->GetName()) { return true; }
    }
    return false;
}

void funcsForMenu::PrintDirections(Graph& graph, std::string& station1, std::string& station2){

    //initialization
    std::list<Edge*> edges = GetDirectionEdges(graph, station1, station2);
    float time = 0;
    float delay = 0;
    float totTime = 0;

    std::cout << "****************" << std::endl;
    std::list<Edge*>::iterator iter = edges.begin();
    std::advance(iter, edges.size() - 1);
    std::string line = (*iter)->GetLine();
    std::string direction = (*iter)->GetDirection();
    std::cout << "Start:    " << station1 << ", " << line << "(" << direction << ")" << std::endl; 
    Vertex* s1 = graph.GetVertexByName(station1); 
    Vertex* s2 = nullptr;

    while ((*iter)->GetNeighbor() != s2){
        while (line == (*iter)->GetLine() && direction == (*iter)->GetDirection()){
            time += (*iter)->GetTime();
            delay += (*iter)->GetDelay();
            s2 = (*iter)->GetNeighbor();
            if (iter == edges.begin()) { break; }
            std::advance(iter, -1);
        }
        std::cout << "Travel:   " << line << "(" << direction << "): "  << s1->GetStation()->GetName() << " to " << s2->GetStation()->GetName() << "   [" << std::fixed << std::setprecision(2) << (time + delay) << " mins]";
        if (delay>0) { std::cout << " including" << delay << " mins in delays."; }
        totTime += (time+ delay);
        std::cout << std::endl;
        if (s2 == graph.GetVertexByName(station2)) { break; }
        std::cout << "Change:   " << s2->GetStation()->GetName() << " - " << line << "(" << direction << ") to " << (*iter)->GetLine() << "(" << (*iter)->GetDirection() << ")   [2.00 mins]";
        totTime += 2.00f;
        std::cout << std::endl;
        time = 0; delay = 0;
        line = (*iter)->GetLine(); direction = (*iter)->GetDirection();
        s1 = s2;
    }
    std::cout << "End:      " << station2 << ", " << line << "(" << direction << ")" << std::endl;
    std::cout << "Total journey time: [" << std::fixed << std::setprecision(2) << totTime << " mins]" << std::endl;
    std::cout << "****************" << std::endl;    
}



bool funcsForMenu::AddDelay(Graph& graph, std::string& startStation, std::string& endStation, std::string& line, float& delay)
{
    Vertex* vertex = graph.GetVertexByName(startStation);
    std::list<Edge*> edges = vertex->GetEdges();
    for (Edge* edge : edges)
    {
        if (edge->GetNeighbor()->GetStation()->GetName() == endStation && edge->GetLine() == line)
        {
            edge->SetDelay(delay);
            return true;
        }
    }
    return false;
}
bool funcsForMenu::RemoveDelay(Graph& graph, std::string& startStation, std::string& endStation, std::string& line)
{
    Vertex* vertex = graph.GetVertexByName(startStation);
    std::list<Edge*> edges = vertex->GetEdges();
    for (Edge* edge : edges)
    {
        if (edge->GetNeighbor()->GetStation()->GetName() == endStation && edge->GetLine() == line)
        {
            edge->SetDelay(0);
            return true;
        }
    }
    return false;
}

bool funcsForMenu::CloseEdge(Graph& graph, std::string& startStation, std::string& endStation, std::string& line)
{
    Vertex* vertex = graph.GetVertexByName(startStation);
    std::list<Edge*> edges = vertex->GetEdges();
    for (Edge* edge : edges)
    {
        if (edge->GetNeighbor()->GetStation()->GetName() == endStation && edge->GetLine() == line)
        {
            edge->CloseEdge();
            return true;
        }
    }
    return false;
}
bool funcsForMenu::OpenEdge(Graph& graph, std::string& startStation, std::string& endStation, std::string& line)
{
    Vertex* vertex = graph.GetVertexByName(startStation);
    std::list<Edge*> edges = vertex->GetEdges();
    for (Edge* edge : edges)
    {
        if (edge->GetNeighbor()->GetStation()->GetName() == endStation && edge->GetLine() == line)
        {
            edge->OpenEdge();
            return true;
        }
    }
    return false;
}