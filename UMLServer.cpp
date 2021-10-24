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

using namespace std;
using namespace restbed;


void get_method_handler(const std::shared_ptr<Session> session);

UMLServer::UMLServer(UMLModel* model)
	: Model(model)
{
    ServerResources = make_shared< Resource >();
    ServerSetting = make_shared< Settings >();

	ServerResources->set_path("/");
	ServerResources->set_method_handler("GET", get_method_handler);

	ServerSetting->set_port(8080);
	ServerSetting->set_default_header("Connection", "close");
}

UMLServer::~UMLServer()
{};


void get_method_handler(const std::shared_ptr<Session> session)
{
    const auto request = session->get_request();
    const string fileName = "./resources/home.html";
    ifstream stream(fileName, ifstream::in);

    if (stream.is_open())
    {
        const string body = string(istreambuf_iterator< char >(stream), istreambuf_iterator< char >());

        const multimap< string, string > headers
        {
            { "Content-Type", "text/html" },
            { "Content-Length", ::to_string(body.length()) }
        };

        session->close(OK, body, headers);
    }
    else
    {
        session->close(NOT_FOUND);
    }
}

int UMLServer::execute()
{
	Service service;
	service.publish(ServerResources);
	service.start(ServerSetting);
	return EXIT_SUCCESS;
}