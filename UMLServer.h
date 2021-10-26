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

class UMLServer {
	private:
		std::shared_ptr<Resource> AddClassResource;
		std::shared_ptr<Resource> AddRelationshipResource;
		std::shared_ptr<Resource> GetModelDataResource;
		std::shared_ptr<Resource> DeleteClassResource;
		std::shared_ptr<Resource> DeleteRelationshipResource;

		UMLModel* Model;
		std::shared_ptr<Settings> ServerSetting;

	public:
		UMLServer(UMLModel* model);
		~UMLServer();

		void post_add_class_handler(const std::shared_ptr<Session> session);
		void post_add_relationship_handler(const std::shared_ptr<Session> session);
		void get_all_data_handler(const std::shared_ptr<Session> session);
		void delete_class_handler(const std::shared_ptr<Session> session);
		void delete_relationship_handler(const std::shared_ptr<Session> session);

		int execute();

};


#endif