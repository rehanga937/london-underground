#include <iostream>
#include <string>

#include "edge.h"

Edge::Edge(Vertex* _neighbor, float _time, std::string _line, std::string _direction){
    neighbor = _neighbor;
    time = _time;
    line = _line;
    direction = _direction;
    delay = 0;
    open = true;
}

void Edge::Print(){
    std::cout << "To "  << neighbor->GetStation()->GetName() << " on " << line << "(" << direction << ") taking " << time << " mins + a delay of " << delay << " mins";
}