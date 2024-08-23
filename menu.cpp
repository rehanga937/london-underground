#include <string>

#include "menu.h"
#include "funcsForMenu.h"


/*MAIN MENU*/

void Menu::MainMenuContainer(Graph& graph){
    bool exit = false;
    while (!exit)
    {
        exit = MainMenu(graph);
    }
}

bool Menu::MainMenu(Graph& graph){
    std::cout << std::endl << std::endl;
    std::cout << "////////// MAIN MENU //////////" << std::endl;
    std::cout << "1 - Engineer Menu." << std::endl ;
    std::cout << "2 - Customer Menu." << std::endl;
    std::cout << "3 - Exit.";
    std::cout << std::endl;
    std::string input;
    std::getline(std::cin, input);

    if (input == "1") {EngineerMenuContainer(graph);}
    else if (input == "2") {CustomerMenuContainer(graph);}
    else if (input == "3") {return true;}
    else {std::cout << "Invalid input.";}
    return false;
}








/*CUSTOMER MENU*/

bool Menu::CustomerMenuContainer(Graph& graph)
{
    bool exit = false;
    while (!exit)
    {
        exit = CustomerMenu(graph);
    }
    return false;
}

bool Menu::CustomerMenu(Graph& graph)
{
    std::cout << std::endl;
    std::cout << "////////// CUSTOMER MENU //////////"<< std::endl;
    std::cout <<"1 - Print available Stations."<< std::endl;
    std::cout <<"2 - Find the quickest route between 2 stations."<< std::endl;
    std::cout <<"3 - Exit."<< std::endl;
    std::cout << std::endl;
    std::string input;
    std::getline(std::cin, input);

    if (input == "1") {PrintStationList(graph);}
    else if (input == "2") {RouteFindingWizard(graph);}
    else if (input == "3") {return true;}
    else {std::cout << "Invalid input.";}
    return false;
}

void Menu::PrintStationList(Graph& graph)
{
    std::cout << std::endl;
    std::cout << "Available stations:";
    for (Vertex* v : graph.GetVertices()){
        std::cout << "     ";
        v->GetStation()->PrintStationName();
        std::cout << std::endl;
    }
}

void Menu::RouteFindingWizard(Graph& graph)
{
    std::cout << "Enter start station" << std::endl;
    std::string start; std::getline(std::cin, start);    
    std::cout << std::endl;
    if (!funcsForMenu::IsStationValid(graph, start))
    {
        std::cout << start << " is an invalid station.";
        return;
    }
    std::cout <<"Enter destination station" << std::endl;
    std::string end;
    std::getline(std::cin, end); 
    if (!funcsForMenu::IsStationValid(graph, end))
    {
        std::cout << end << " is an invalid station.";
        return;
    }
    funcsForMenu::PrintDirections(graph, start, end);
}





/*ENGINEER MENU*/
bool Menu::EngineerMenuContainer(Graph& graph)
{
    bool exit = false;
    while (!exit)
    {
        exit = EngineerMenu(graph);
    }
    return false;
}

bool Menu::EngineerMenu(Graph& graph)
{
    std::cout << std::endl << std::endl;
    std::cout << "////////// ENGINEER MENU //////////" << std::endl;
    std::cout << "1 - Print entire network." << std::endl;
    std::cout << "2 - Add delays." << std::endl;
    std::cout << "3 - Remove delays." << std::endl;
    std::cout << "4 - Print delayed track sections." << std::endl;
    std::cout << "5 - Close track section." << std::endl;
    std::cout << "6 - Open track section." << std::endl;
    std::cout << "7 - Print closed track sections." << std::endl;
    std::cout << "8 - Exit." << std::endl;
    std::cout << std::endl;
    std::string input;
    std::getline(std::cin, input);
    if (input == "1") {
        graph.Print();
    } else if (input == "2") {
        Menu::AddDelayWizard(graph);
    } else if (input == "3") {
        RemoveDelayWizard(graph);
    } else if (input == "4") {
        PrintDelays(graph);
    } else if (input == "5") {
        CloseEdgeWizard(graph);
    } else if (input == "6") {
        OpenEdgeWizard(graph);
    } else if (input == "7") {
        PrintClosedTrackSections(graph);
    } else if (input == "8") {
        return true;
    } else {
        std::cout << "Invalid input." << std::endl;
    }

    return false;
} 

void Menu::AddDelayWizard(Graph& graph)
{
    std::cout << "Enter start station";
    std::string start;
    std::getline(std::cin, start);
    if (!funcsForMenu::IsStationValid(graph, start))
    {
        std::cout <<"Invalid station";
        return;
    }
    std::cout << "Enter destination station";
    std::string end;
    std::getline(std::cin, end);
    if (!funcsForMenu::IsStationValid(graph, end))
    {
        std::cout << "Invalid station";
        return;
    }
    std::cout << "Enter line";
    std::string line;
    std::getline(std::cin, line);
    std::cout << "Enter delay";
    std::string delay;
    std::getline(std::cin, delay);
    float delayValue = 0;
    try
    {
        delayValue = std::stof(delay);
    }catch(...)
    {
        std::cout << "Invalid input for delay value.";
        return;
    }
    if (delayValue < 0)
    {
        std::cout << "Delay value cannot be negative.";
        return;
    }
    bool result = funcsForMenu::AddDelay(graph,start, end,line, delayValue);
    if (!result)
    {
        std::cout << "Error. Check line name or check if there is a station in-between the provided stations.";
    }
    else
    {
        std::cout << "Delay added successfully";
    }
}

void Menu::RemoveDelayWizard(Graph& graph)
{
    std::cout << "Enter start station";
    std::string start;
    std::getline(std::cin, start);
    if (!funcsForMenu::IsStationValid(graph, start))
    {
        std::cout <<"Invalid station";
        return;
    }
    std::cout << "Enter destination station";
    std::string end;
    std::getline(std::cin, end);
    if (!funcsForMenu::IsStationValid(graph, end))
    {
        std::cout << "Invalid station";
        return;
    }
    std::cout << "Enter line";
    std::string line;
    std::getline(std::cin, line);
    bool result = funcsForMenu::RemoveDelay(graph, start, end, line);
    if (!result)
    {
        std::cout << "Error. Check line name or check if there is a station in-between the provided stations.";
    }
    else
    {
        std::cout << "Delay removed successfully";
    }
}

void Menu::PrintDelays(Graph& graph)
{
    std::cout << "Delays:";
    std::cout << std::endl;
    for (Vertex* v : graph.GetVertices())
    {
        for (Edge* e : v->GetEdges())
        {
            if (e->GetDelay() > 0)
            {
                v->GetStation()->PrintStationName();
                std::cout <<" to ";
                e->Print();
            }
        }
    }
}

void Menu::CloseEdgeWizard(Graph& graph)
{
    std::cout << "Enter start station";
    std:: string start; std::getline(std::cin, start);
    if (!funcsForMenu::IsStationValid(graph, start))
    {
        std::cout << "Invalid station";
        return;
    }
    std::cout << "Enter destination station";
    std::string end; std::getline(std::cin, end);
    if (!funcsForMenu::IsStationValid(graph, end))
    {
        std::cout << "Invalid station";
        return;
    }
    std::cout << "Enter line";
    std::string line; std::getline(std::cin, line);
    bool result = funcsForMenu::CloseEdge(graph, start, end, line);
    if (!result)
    {
        std::cout << "Error. Check line name or check if there is a station in-between the provided stations.";
    }
    else
    {
        std::cout << "Track closed successfully";
    }
}

void Menu::OpenEdgeWizard(Graph& graph)
{
    std::cout << "Enter start station";
    std:: string start; std::getline(std::cin, start);
    if (!funcsForMenu::IsStationValid(graph, start))
    {
        std::cout << "Invalid station";
        return;
    }
    std::cout << "Enter destination station";
    std::string end; std::getline(std::cin, end);
    if (!funcsForMenu::IsStationValid(graph, end))
    {
        std::cout << "Invalid station";
        return;
    }
    std::cout << "Enter line";
    std::string line; std::getline(std::cin, line);
    bool result = funcsForMenu::OpenEdge(graph, start, end, line);
    if (!result)
    {
        std::cout << "Error. Check line name or check if there is a station in-between the provided stations.";
    }
    else
    {
        std::cout << "Track closed successfully";
    }
}

void Menu::PrintClosedTrackSections(Graph& graph)
{
    std::cout << "Closed track sections:";
    std::cout << std::endl;;
    for (Vertex* v : graph.GetVertices())
    {
        for (Edge* e : v->GetEdges())
        {
            if (!e->IsOpen())
            {
                v->GetStation()->PrintStationName();
                std::cout << " to ";
                e->GetNeighbor()->GetStation()->PrintStationName();
            }
        }
    }
}