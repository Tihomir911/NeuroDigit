#include "HttpServer.hpp"

#include <filesystem>

#include <httplib.h>
#include <nlohmann/json.hpp>

#include <iostream>
#include <vector>

using namespace std;
using json = nlohmann::json;


void startServer(
    NeuralNetwork& network
)
{
    httplib::Server server;


    cout << "Starting HTTP server..." << endl;


    server.Post(
        "/predict",
        [&](const httplib::Request& request,
            httplib::Response& response)
        {
            try
            {
                json data =
                    json::parse(request.body);


                if (!data.contains("pixels"))
                {
                    response.status = 400;

                    response.set_content(
                        R"({"error":"Missing pixels field"})",
                        "application/json"
                    );

                    return;
                }

                vector<double> pixels =
                    data["pixels"].get<vector<double>>();


                if (pixels.size() != 784)
                {
                    response.status = 400;

                    response.set_content(
                        R"({"error":"Expected 784 pixels"})",
                        "application/json"
                    );

                    return;
                }

                vector<double> probabilities =
                    network.predict(pixels);


                int prediction = 0;


                for (int i = 1; i < 10; i++)
                {
                    if (probabilities[i] >
                        probabilities[prediction])
                    {
                        prediction = i;
                    }
                }


                double confidence =
                    probabilities[prediction];


                json result;

                result["prediction"] = prediction;
                result["confidence"] = confidence;


                response.set_content(
                    result.dump(),
                    "application/json"
                );
            }
            catch (const exception& error)
            {
                response.status = 400;

                json result;

                result["error"] = error.what();


                response.set_content(
                    result.dump(),
                    "application/json"
                );
            }
        }
    );

    string frontendPath;

    if (filesystem::is_directory("./frontend"))
    {
        frontendPath = "./frontend";
    }
    else if (filesystem::is_directory("./build/frontend"))
    {
        frontendPath = "./build/frontend";
    }
    else if (filesystem::is_directory("../frontend"))
    {
        frontendPath = "../frontend";
    }
    else
    {
        cerr << "Failed to find frontend directory." << endl;
        cerr << "Checked:" << endl;
        cerr << "  ./frontend" << endl;
        cerr << "  ./build/frontend" << endl;
        cerr << "  ../frontend" << endl;

        return;
    }

    cout << "Frontend directory found: "
         << frontendPath
         << endl;

    if (!server.set_mount_point("/", frontendPath))
    {
        cerr << "Failed to mount frontend directory: "
             << frontendPath
             << endl;

        return;
    }

    cout << "Server is running on:" << endl;
    cout << "http://localhost:8080" << endl;

    server.listen(
        "0.0.0.0",
        8080
    );
}