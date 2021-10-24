#include <iostream>
#include <string>

#include "UMLClass.h"
#include "UMLController.h"
#include "UMLModel.h"
#include "UMLRelationship.h"
#include "UMLServer.h"

void run_cli()
{
    UMLModel model;
    UMLController controller{ model };
    controller.execute();
}

void run_gui()
{
    // Create model and view
    // View constructs stuff such as buttons and other UI elements
    UMLModel model;
    UMLServer server{ &model };

    std::cout << "Starting server on localhost:8080" << std::endl;
    server.execute();
}

int main(int argc, char** argv)
{

    if (argc > 1)
    {
        if (string(argv[1]) == "--cli")
        {
            run_cli();
        }
        else if (string(argv[1]) == "--gui")
        {
            run_gui();
        }
        else
        {
            std::cout << "Unknown UI flag. Use either --cli or --gui" << std::endl;
        }
    }
    else
    {
        run_gui();
    }

    return 0;
}