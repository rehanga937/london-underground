#include <fstream>
#include <sstream>
#include <string>

#include "station.h"
#include "edge.h"
#include "vertex.h"
#include "graph.h"
#include "menu.h"

int main(){


    /*create graph with all tube stations and overground stations*/
    Graph graph;
    std::string line;    
    char delimiter = ',';
    std::string cells[5];
    std::ifstream file("../Import Rail Network/All Stations.csv");
    if (!file.is_open()) {
        std::cerr << "Error - cannot open input file." << std::endl;
        return 1;
    }
    std::getline(file,line);//skip first row (header row)       
    while (std::getline(file,line)){
        graph.AddVertex(*new Vertex(*new Station(line)));
    }    
    file.close();

    
    /*add edges for the 91 tubestations*/
    file.open("../Import Rail Network/Tube Edges.csv");
    if (!file.is_open()) {
        std::cerr << "Error - cannot open input file." << std::endl;
        return 1;
    }
    std::getline(file,line);//skip first row (header row)       
    while (std::getline(file,line)){
        std::stringstream ss(line);
        for(int i = 0; i < 5; i++){
            std::getline(ss,cells[i],delimiter);
        }
        graph.GetVertexByName(cells[2])->AddEdge(*(new Edge(graph.GetVertexByName(cells[3]),std::stof(cells[4]),cells[0], cells[1])));
    }    
    file.close();
    

    /*add edges for the overground stations*/
    file.open("../Import Rail Network/Overground Edges.csv");
    if (!file.is_open()) {
        std::cerr << "Error - cannot open input file." << std::endl;
        return 1;
    }
    std::getline(file,line);//skip first row (header row)       
    while (std::getline(file,line)){
        std::stringstream ss(line);
        for(int i = 0; i < 5; i++){
            std::getline(ss,cells[i],delimiter);
        }
        graph.GetVertexByName(cells[2])->AddEdge(*(new Edge(graph.GetVertexByName(cells[3]),std::stof(cells[4]),cells[0], cells[1])));
    }    
    file.close();
    

    /*run the CLI*/
    Menu::MainMenuContainer(graph);


    /*Clear dynamically allocated memory*/
    for (Vertex* v : graph.GetVertices()){
        delete (v->GetStation());
        for (Edge* e : v->GetEdges()){
            delete e;
        }
        delete v;
    }
        

    return 0;
}
