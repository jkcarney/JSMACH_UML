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
		std::shared_ptr<Resource> AddClassResource;
		std::shared_ptr<Resource> GetModelDataResource;
		std::shared_ptr<Settings> ServerSetting;

	public:
		UMLServer(UMLModel* model);
		~UMLServer();

		void add_class_handler(const std::shared_ptr<Session> session);
		void get_all_data_handler(const std::shared_ptr<Session> session);

		int execute();

};


#endif