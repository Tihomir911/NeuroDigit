#include "NeuralNetwork.hpp"
#include "Mnist.hpp"
#include "HttpServer.hpp"

#include <iostream>
#include <iomanip>
#include <string>

using namespace std;


void trainModel()
{
    Mnist trainDataset;
    Mnist testDataset;


    cout << "Loading MNIST..." << endl;


    trainDataset.loadImages(
        "data/mnist/train-images-idx3-ubyte"
    );

    trainDataset.loadLabels(
        "data/mnist/train-labels-idx1-ubyte"
    );


    testDataset.loadImages(
        "data/mnist/t10k-images-idx3-ubyte"
    );

    testDataset.loadLabels(
        "data/mnist/t10k-labels-idx1-ubyte"
    );


    cout << "Training images: "
         << trainDataset.images.size()
         << endl;

    cout << "Training labels: "
         << trainDataset.labels.size()
         << endl;

    cout << "Test images: "
         << testDataset.images.size()
         << endl;

    cout << "Test labels: "
         << testDataset.labels.size()
         << endl;


    NeuralNetwork network;


    const double learningRate = 0.01;


    cout << endl;
    cout << "Starting training..." << endl;
    cout << endl;


    for (int i = 0; i < 60000; i++)
    {
        network.train(
            trainDataset.images[i],
            trainDataset.labels[i],
            learningRate
        );


        if (i % 1000 == 0)
        {
            cout << "Training: "
                 << i
                 << " / 60000"
                 << endl;
        }
    }


    cout << endl;
    cout << "Training finished!" << endl;


    network.save("model.bin");


    cout << "Model saved to model.bin"
         << endl;


    cout << endl;
    cout << "Testing model..." << endl;


    int correct = 0;


    for (int i = 0; i < 10000; i++)
    {
        vector<double> probabilities =
            network.predict(
                testDataset.images[i]
            );


        int prediction = 0;


        for (int j = 1; j < 10; j++)
        {
            if (probabilities[j] >
                probabilities[prediction])
            {
                prediction = j;
            }
        }


        if (prediction ==
            testDataset.labels[i])
        {
            correct++;
        }


        if (i % 1000 == 0)
        {
            cout << "Testing: "
                 << i
                 << " / 10000"
                 << endl;
        }
    }


    double accuracy =
        static_cast<double>(correct)
        / 10000.0
        * 100.0;


    cout << endl;

    cout << "Correct: "
         << correct
         << " / 10000"
         << endl;


    cout << fixed
         << setprecision(2);

    cout << "Accuracy: "
         << accuracy
         << "%"
         << endl;
}


int main(
    int argc,
    char* argv[]
)
{
    if (argc < 2)
    {
        cout << "Usage:" << endl;

        cout << "  ./NeuroDigit train"
             << endl;

        cout << "  ./NeuroDigit server"
             << endl;

        return 1;
    }


    string mode = argv[1];


    if (mode == "train")
    {
        trainModel();

        return 0;
    }


    if (mode == "server")
    {
        NeuralNetwork network;


        cout << "Loading model..." << endl;

        network.load("model.bin");


        cout << "Model loaded!" << endl;


        startServer(network);


        return 0;
    }


    cout << "Unknown mode: "
         << mode
         << endl;

    cout << endl;

    cout << "Available modes:" << endl;

    cout << "  train" << endl;
    cout << "  server" << endl;


    return 1;
}