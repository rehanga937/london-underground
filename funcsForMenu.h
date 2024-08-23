#include <list>
#include <string>

#include "edge.h"
#include "graph.h"

class funcsForMenu{
    private:

        static std::list<Edge*> GetDirectionEdges(Graph&, std::string&, std::string&);//returns LinkedList of edges indiciating the shortest path of a journey

    public: /*all of these are only used by menu.cpp*/

        static bool IsStationValid(Graph&, std::string&);

        static void PrintDirections(Graph&, std::string&, std::string&);//transcribes the shortest path of a journey into a customer friendly format on the console

        static bool AddDelay(Graph&, std::string&, std::string&, std::string&, float&);
        static bool RemoveDelay(Graph&, std::string&, std::string&, std::string&);
        
        static bool CloseEdge(Graph&, std::string&, std::string&, std::string&);
        static bool OpenEdge(Graph&, std::string&, std::string&, std::string&);


};