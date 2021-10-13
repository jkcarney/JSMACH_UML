#ifndef UML_GUI_CONTROLLER
#define UML_GUI_CONTROLLER

#include "UMLModel.h"
#include "GUIView.h"
#include <string>


class GUIController {
	private:
		UMLModel* Model;
		GUIView* View;

	public:
		GUIController(UMLModel& model, GUIView& view);
        ~GUIController();
};      


#endif