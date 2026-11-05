
#include "NeuralNetwork.hpp"
#include "Mnist.hpp"
#include "HttpServer.hpp"
#include "TerminalUI.hpp"

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <array>
#include <algorithm>
#include <cmath>
#include <stdexcept>

using namespace std;


// ============================================================
// DATASET LOADING
// ============================================================

Mnist loadTestDataset()
{
    Mnist dataset;

    cout << "Loading MNIST test dataset..." << endl;

    dataset.loadImages(
        "data/mnist/t10k-images-idx3-ubyte"
    );

    dataset.loadLabels(
        "data/mnist/t10k-labels-idx1-ubyte"
    );

    if (dataset.images.empty())
    {
        throw runtime_error("Test dataset is empty");
    }

    if (dataset.images.size() != dataset.labels.size())
    {
        throw runtime_error(
            "Number of images and labels does not match"
        );
    }

    cout << "Loaded images: "
         << dataset.images.size()
         << endl;

    cout << "Loaded labels: "
         << dataset.labels.size()
         << endl;

    return dataset;
}


// ============================================================
// PREDICTION
// ============================================================

int getPrediction(
    const vector<double>& probabilities
)
{
    if (probabilities.empty())
    {
        throw runtime_error(
            "Network returned empty probabilities"
        );
    }

    return static_cast<int>(
        max_element(
            probabilities.begin(),
            probabilities.end()
        ) - probabilities.begin()
    );
}


// ============================================================
// MODEL EVALUATION
// ============================================================

void evaluateModel()
{
    cout << "====================================" << endl;
    cout << "          NEURODIGIT EVALUATION" << endl;
    cout << "====================================" << endl;

    Mnist testDataset = loadTestDataset();

    NeuralNetwork network;

    cout << endl;
    cout << "Loading model.bin..." << endl;

    network.load("model.bin");

    cout << "Model loaded successfully!" << endl;

    cout << endl;
    cout << "Starting evaluation..." << endl;
    cout << endl;


    int correct = 0;
    int incorrect = 0;

    double totalLoss = 0.0;

    array<array<int, 10>, 10> confusionMatrix{};

    array<int, 10> classCorrect{};
    array<int, 10> classTotal{};

    const int totalSamples =
        static_cast<int>(testDataset.images.size());


    for (int i = 0; i < totalSamples; i++)
    {
        const vector<double>& image =
            testDataset.images[i];

        const int label =
            testDataset.labels[i];

        if (label < 0 || label >= 10)
        {
            throw runtime_error(
                "Invalid label in test dataset"
            );
        }


        vector<double> probabilities =
            network.predict(image);


        if (probabilities.size() != 10)
        {
            throw runtime_error(
                "Network must return 10 probabilities"
            );
        }


        int prediction =
            getPrediction(probabilities);


        // Cross-Entropy Loss

        const double epsilon = 1e-15;

        double probability =
            max(
                probabilities[label],
                epsilon
            );

        totalLoss -= log(probability);


        // Accuracy

        confusionMatrix[label][prediction]++;

        classTotal[label]++;


        if (prediction == label)
        {
            correct++;
            classCorrect[label]++;
        }
        else
        {
            incorrect++;
        }


        // Progress

        if ((i + 1) % 1000 == 0 ||
            i + 1 == totalSamples)
        {
            double progress =
                static_cast<double>(i + 1)
                / totalSamples
                * 100.0;

            cout << "\rEvaluating: "
                 << i + 1
                 << " / "
                 << totalSamples
                 << " ("
                 << fixed
                 << setprecision(1)
                 << progress
                 << "%)"
                 << flush;
        }
    }


    // ========================================================
    // FINAL METRICS
    // ========================================================

    double accuracy =
        static_cast<double>(correct)
        / totalSamples
        * 100.0;

    double averageLoss =
        totalLoss / totalSamples;


    cout << endl;
    cout << endl;

    cout << "====================================" << endl;
    cout << "          EVALUATION RESULTS" << endl;
    cout << "====================================" << endl;

    cout << fixed << setprecision(4);

    cout << "Total samples: "
         << totalSamples
         << endl;

    cout << "Correct: "
         << correct
         << endl;

    cout << "Incorrect: "
         << incorrect
         << endl;

    cout << "Accuracy: "
         << setprecision(2)
         << accuracy
         << "%"
         << endl;

    cout << "Average Loss: "
         << setprecision(6)
         << averageLoss
         << endl;


    // ========================================================
    // PER-CLASS ACCURACY
    // ========================================================

    cout << endl;
    cout << "====================================" << endl;
    cout << "          CLASS ACCURACY" << endl;
    cout << "====================================" << endl;

    cout << "Digit | Correct | Total | Accuracy" << endl;
    cout << "------------------------------------" << endl;

    for (int digit = 0; digit < 10; digit++)
    {
        double classAccuracy = 0.0;

        if (classTotal[digit] > 0)
        {
            classAccuracy =
                static_cast<double>(classCorrect[digit])
                / classTotal[digit]
                * 100.0;
        }

        cout << setw(5) << digit
             << " | "
             << setw(7) << classCorrect[digit]
             << " | "
             << setw(5) << classTotal[digit]
             << " | "
             << fixed
             << setprecision(2)
             << classAccuracy
             << "%"
             << endl;
    }


    // ========================================================
    // CONFUSION MATRIX
    // ========================================================

    cout << endl;
    cout << "====================================" << endl;
    cout << "          CONFUSION MATRIX" << endl;
    cout << "====================================" << endl;

    cout << "Rows = actual digit" << endl;
    cout << "Columns = predicted digit" << endl;
    cout << endl;

    cout << "Actual\\Pred ";

    for (int digit = 0; digit < 10; digit++)
    {
        cout << setw(5) << digit;
    }

    cout << endl;

    for (int actual = 0; actual < 10; actual++)
    {
        cout << setw(11) << actual;

        for (int predicted = 0; predicted < 10; predicted++)
        {
            cout << setw(5)
                 << confusionMatrix[actual][predicted];
        }

        cout << endl;
    }

    cout << endl;
    cout << "Evaluation completed!" << endl;
}


// ============================================================
// TRAINING
// ============================================================

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

    if (trainDataset.images.size() != trainDataset.labels.size()){

        throw runtime_error(
            "Training images and labels count missmatch"
        );
    }
    if (trainDataset.images.empty()){

        throw runtime_error(
            "Training dataset is empty"
        );
    }

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


    for (size_t i = 0; i < trainDataset.images.size(); i++){

        network.train(
            trainDataset.images[i],
            trainDataset.labels[i],
            learningRate
        );

        if (i % 1000 == 0)
        {
            cout << "Training: "
             << i
             << " / "
             << trainDataset.images.size()
             << endl;
        }
    }


    cout << endl;
    cout << "Training finished!" << endl;

    network.save("model.bin");

    cout << "Model saved to model.bin" << endl;
}


// ============================================================
// MAIN
// ============================================================

int main(
    int argc,
    char* argv[]
)
{
    try
    {
        if (argc < 2)
        {
            cout << "Usage:" << endl;
            cout << "  ./NeuroDigit train" << endl;
            cout << "  ./NeuroDigit evaluate" << endl;
            cout << "  ./NeuroDigit server" << endl;

            return 1;
        }


        string mode = argv[1];


        if (mode == "train")
        {
            trainModel();
            return 0;
        }


        if (mode == "evaluate")
        {
            evaluateModel();
            return 0;
        }

        if (mode == "server")
        {
            NeuralNetwork network;

            network.load("model.bin");

            startServer(network);

            return 0;
        }

        cout << "Unknown mode: "
             << mode
             << endl;

        cout << endl;
        cout << "Available modes:" << endl;
        cout << "  train" << endl;
        cout << "  evaluate" << endl;
        cout << "  server" << endl;

        return 1;
    }
    catch (const exception& error)
    {
        TerminalUI::printError(error.what());
        return 1;
    }
}
