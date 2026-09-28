#include "NeuralNetwork.hpp"

#include <cmath>
#include <random>
#include <fstream>
#include <stdexcept>

using namespace std;

NeuralNetwork::NeuralNetwork()
{
    // Network architecture:
    // 784 -> 128 -> 64 -> 10

    weightsInputHidden1.resize(128, vector<double>(784));
    biasHidden1.resize(128);

    weightsHidden1Hidden2.resize(64, vector<double>(128));
    biasHidden2.resize(64);

    weightsHidden2Output.resize(10, vector<double>(64));
    biasOutput.resize(10);

    random_device rd;
    mt19937 generator(rd());

    normal_distribution<double> distribution(0.0, 0.01);

    for (auto& neuron : weightsInputHidden1)
    {
        for (double& weight : neuron)
        {
            weight = distribution(generator);
        }
    }

    for (auto& neuron : weightsHidden1Hidden2)
    {
        for (double& weight : neuron)
        {
            weight = distribution(generator);
        }
    }

    for (auto& neuron : weightsHidden2Output)
    {
        for (double& weight : neuron)
        {
            weight = distribution(generator);
        }
    }
}


double NeuralNetwork::relu(double value)
{
    if (value > 0.0)
    {
        return value;
    }

    return 0.0;
}


double NeuralNetwork::reluDerivative(double value)
{
    if (value > 0.0)
    {
        return 1.0;
    }

    return 0.0;
}