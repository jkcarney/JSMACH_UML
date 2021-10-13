#include "GUIController.h"
#include "UMLModel.h"
#include "GUIView.h"
#include <iostream>
#include "UMLException.hpp"


GUIController::GUIController(UMLModel& model, GUIView& view)
	: Model(&model), View(&view)
{}

GUIController::~GUIController() {}


