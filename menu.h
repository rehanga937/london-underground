#include "graph.h"

class Menu{
    private:

        /*MAIN MENU*/
        static bool MainMenu(Graph&);

        /*CUSTOMER MENU*/
        static bool CustomerMenuContainer(Graph&);
        static bool CustomerMenu(Graph&);
        static void PrintStationList(Graph&);
        static void RouteFindingWizard(Graph&);

        /*ENGINEER MENU*/
        static bool EngineerMenuContainer(Graph&);
        static bool EngineerMenu(Graph&);
        static void AddDelayWizard(Graph&);
        static void RemoveDelayWizard(Graph&);
        static void PrintDelays(Graph&);
        static void CloseEdgeWizard(Graph&);
        static void OpenEdgeWizard(Graph&);
        static void PrintClosedTrackSections(Graph&);


    public:

        /*MAIN MENU*/
        static void MainMenuContainer(Graph&);


};