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
using namespace restbed;
using json = nlohmann::json;

UMLServer::UMLServer(UMLModel* model)
	: Model(model)
{
	AddClassResource = std::make_shared<Resource>();
	AddRelationshipResource = std::make_shared<Resource>();
	GetModelDataResource = std::make_shared<Resource>();
	DeleteClassResource = std::make_shared<Resource>();
	DeleteRelationshipResource = std::make_shared<Resource>();

    ServerSetting = std::make_shared<Settings>();

	// need the std::bind because otherwise we can't use member functions directly
	AddClassResource->set_path("/addclass");
	AddClassResource->set_method_handler("POST", std::bind(&UMLServer::post_add_class_handler, this, _1));

	AddRelationshipResource->set_path("/addrelationship");
	AddRelationshipResource->set_method_handler("POST", std::bind(&UMLServer::post_add_relationship_handler, this, _1));

	GetModelDataResource->set_path("/data");
	GetModelDataResource->set_method_handler("GET", std::bind(&UMLServer::get_all_data_handler, this, _1));

	DeleteClassResource->set_path("/deleteclass");
	DeleteClassResource->set_method_handler("DELETE", std::bind(&UMLServer::delete_class_handler, this, _1));

	DeleteRelationshipResource->set_path("/deleterelationship");
	DeleteRelationshipResource->set_method_handler("DELETE", std::bind(&UMLServer::delete_relationship_handler, this, _1));

	ServerSetting->set_port(8080);
	ServerSetting->set_default_header("Connection", "close");
}

UMLServer::~UMLServer()
{};

void UMLServer::get_all_data_handler(const std::shared_ptr<Session> session)
{
	const auto request = session->get_request();
	json data = *Model;
	session->close(OK, data.dump());
}

void UMLServer::post_add_class_handler(const std::shared_ptr<Session> session)
{
    const auto request = session->get_request();
	std::multimap query = request->get_query_parameters();
	//const std::string className = query.find("class")->second;
	//TODO: add class shit lmao
	//probably close with error code if cant add
    session->close(OK);
}

void UMLServer::post_add_relationship_handler(const std::shared_ptr<Session> session)
{
	const auto request = session->get_request();
	std::multimap query = request->get_query_parameters();

	RelationshipType rType = UMLRelationship::type_from_string(query.find("type")->second);
	const std::string srcName = query.find("src")->second;
	const std::string destName = query.find("dest")->second;

	if (Model->add_relationship(srcName, destName, rType))
		session->close(OK);
	else
		session->close(BAD_REQUEST);
}

void UMLServer::delete_class_handler(const std::shared_ptr<Session> session)
{
	const auto request = session->get_request();
	const std::string className = request->get_query_parameter("name");

	if (Model->remove_class(className))
		session->close(OK);
	else
		session->close(BAD_REQUEST);
}

void UMLServer::delete_relationship_handler(const std::shared_ptr<Session> session)
{
	const auto request = session->get_request();
	const std::string srcName = request->get_query_parameter("src");
	const std::string destName = request->get_query_parameter("dest");

	if (Model->remove_relationship(srcName, destName))
		session->close(OK);
	else
		session->close(BAD_REQUEST);
}

int UMLServer::execute()
{
	Service service;
	
	service.publish(AddClassResource);
	service.publish(AddRelationshipResource);
	service.publish(GetModelDataResource);
	service.publish(DeleteClassResource);
	service.publish(DeleteRelationshipResource);

	service.start(ServerSetting);
	return EXIT_SUCCESS;
}