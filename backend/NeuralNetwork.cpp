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

vector<double> NeuralNetwork::forward(
    const vector<double>& input
)
{
    vector<double> hidden1(128);

    for (int i = 0; i < 128; i++)
    {
        double sum = biasHidden1[i];

        for (int j = 0; j < 784; j++)
        {
            sum += weightsInputHidden1[i][j] * input[j];
        }

        hidden1[i] = relu(sum);
    }

    vector<double> hidden2(64);

    for (int i = 0; i < 64; i++)
    {
        double sum = biasHidden2[i];

        for (int j = 0; j < 128; j++)
        {
            sum += weightsHidden1Hidden2[i][j] * hidden1[j];
        }

        hidden2[i] = relu(sum);
    }

    vector<double> output(10);

    for (int i = 0; i < 10; i++)
    {
        double sum = biasOutput[i];

        for (int j = 0; j < 64; j++)
        {
            sum += weightsHidden2Output[i][j] * hidden2[j];
        }

        output[i] = sum;
    }

    return output;
    
}