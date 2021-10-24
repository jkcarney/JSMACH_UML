#ifndef UML_SERVER
#define UML_SERVER

#include "UMLModel.h"
#include <iostream>
#include <string>

#include "UMLClass.h"
#include "UMLController.h"
#include "UMLModel.h"
#include "UMLRelationship.h"

#include <memory>
#include <cstdlib>
#include <restbed>
#include <fstream>

using namespace restbed;
using namespace std;

class UMLServer {
	private:
		UMLModel* Model;
		std::shared_ptr<Resource> ServerResources;
		std::shared_ptr<Settings> ServerSetting;

	public:
		UMLServer(UMLModel* model);
		~UMLServer();

		int execute();

};


#endif