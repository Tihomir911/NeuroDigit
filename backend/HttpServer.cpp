#include "HttpServer.hpp"
#include "TerminalUI.hpp"

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

    server.Get(
        "/weights",
        [&](const httplib::Request& request,
            httplib::Response& response)
        {
            json result;

            // INPUT -> HIDDEN 1
            result["inputToHidden1"] =
                network.weightsInputHidden1ForVisualization();

            // HIDDEN 1 -> HIDDEN 2
            result["hidden1ToHidden2"] =
                network.weightsHidden1Hidden2ForVisualization();

            // HIDDEN 2 -> OUTPUT
            result["hidden2ToOutput"] =
                network.weightsHidden2OutputForVisualization();

            response.set_content(
                result.dump(),
                "application/json"
            );
        }
    );

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

                
                PredictionTrace trace =
                    network.predictDetailed(pixels);


                const vector<double>& probabilities =
                    trace.probabilities;


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

                result["input"] = trace.input;
                result["hidden1"] = trace.hidden1;
                result["hidden2"] = trace.hidden2;
                result["logits"] = trace.logits;
                result["output"] = trace.probabilities;

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
        TerminalUI::printError("Failed to find frontend directory.");

        cerr << "Checked:" << endl;
        cerr << "  ./frontend" << endl;
        cerr << "  ./build/frontend" << endl;
        cerr << "  ../frontend" << endl;

        return;
    }

    if (!server.set_mount_point("/", frontendPath))
    {
        TerminalUI::printError(
            "Failed to mount frontend directory: " + frontendPath
        );

        return;
    }

    TerminalUI::printStartupScreen(
        frontendPath,
        "http://localhost:8080"
    );

    if (!server.listen("0.0.0.0", 8080))
    {
        TerminalUI::printError("HTTP server failed to start");
    }
}