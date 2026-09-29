#include "HttpServer.hpp"

#include <httplib.h>
#include <nlohmann/json.hpp>

#include <iostream>

using namespace std;

using json = nlohmann::json;

void startServer(
    NeuralNetwork& network
)
{
    httplib::Server server;

    cout << "Starting HTTP server..." << endl;

    server.listen(
        "0.0.0.0",
        8080
    );
}