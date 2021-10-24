#include "UMLServer.h"
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
#include <nlohmann/json.hpp>


using namespace std::placeholders;
using namespace std;
using namespace restbed;
using json = nlohmann::json;

UMLServer::UMLServer(UMLModel* model)
	: Model(model)
{
	AddClassResource = make_shared< Resource >();
	GetModelDataResource = make_shared< Resource >();
    ServerSetting = make_shared< Settings >();

	// need the std::bind because otherwise we can't use member functions directly
	AddClassResource->set_path("/addclass");
	AddClassResource->set_method_handler("POST", std::bind(&UMLServer::add_class_handler, this, _1));

	GetModelDataResource->set_path("/data");
	GetModelDataResource->set_method_handler("GET", std::bind(&UMLServer::add_class_handler, this, _1));

	ServerSetting->set_port(8080);
	ServerSetting->set_default_header("Connection", "close");
}

UMLServer::~UMLServer()
{};

void UMLServer::get_all_data_handler(const std::shared_ptr<Session> session)
{

}

void UMLServer::add_class_handler(const std::shared_ptr<Session> session)
{
    const auto request = session->get_request();
	multimap query = request->get_query_parameters();
	const string className = query.find("class")->second;
	
    session->close(OK);
}

int UMLServer::execute()
{
	Service service;

	service.publish(AddClassResource);

	service.start(ServerSetting);
	return EXIT_SUCCESS;
}