#ifndef UML_GUI_VIEW
#define UML_GUI_VIEW
#include <string>
#include <list>
#include <vector>
#include "UMLClass.h"
#include "UMLModel.h"
#include "UMLRelationship.h"
#include "ClassField.h"
#include "ClassMethod.h"
#include "MethodParameter.h"


class GUIView {
	private:
		UMLModel* Model;
	public:
		GUIView(UMLModel& model);
		~GUIView();
};



#endif