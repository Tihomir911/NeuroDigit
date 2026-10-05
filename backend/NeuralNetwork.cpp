#include "NeuralNetwork.hpp"

#include <cmath>
#include <random>
#include <fstream>
#include <stdexcept>
#include <algorithm>

using namespace std;


NeuralNetwork::NeuralNetwork()
{
    // 784 -> 128 -> 64 -> 10

    weightsInputHidden1.resize(
        128,
        vector<double>(784)
    );

    biasHidden1.resize(128);

    weightsHidden1Hidden2.resize(
        64,
        vector<double>(128)
    );

    biasHidden2.resize(64);

    weightsHidden2Output.resize(
        10,
        vector<double>(64)
    );

    biasOutput.resize(10);


    random_device rd;
    mt19937 generator(rd());

    normal_distribution<double> distribution(
        0.0,
        0.01
    );


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


vector<double> NeuralNetwork::softmax(
    const vector<double>& values
)
{
    vector<double> probabilities(
        values.size()
    );


    double maxValue = values[0];

    for (double value : values)
    {
        if (value > maxValue)
        {
            maxValue = value;
        }
    }


    double sum = 0.0;

    for (int i = 0; i < values.size(); i++)
    {
        probabilities[i] =
            exp(values[i] - maxValue);

        sum += probabilities[i];
    }


    for (int i = 0; i < probabilities.size(); i++)
    {
        probabilities[i] /= sum;
    }


    return probabilities;
}


vector<double> NeuralNetwork::forward(
    const vector<double>& input,
    vector<double>& hidden1,
    vector<double>& hidden2
)
{
    hidden1.resize(128);

    for (int i = 0; i < 128; i++)
    {
        double sum = biasHidden1[i];


        for (int j = 0; j < 784; j++)
        {
            sum +=
                weightsInputHidden1[i][j]
                * input[j];
        }


        hidden1[i] = relu(sum);
    }

    hidden2.resize(64);


    for (int i = 0; i < 64; i++)
    {
        double sum = biasHidden2[i];


        for (int j = 0; j < 128; j++)
        {
            sum +=
                weightsHidden1Hidden2[i][j]
                * hidden1[j];
        }


        hidden2[i] = relu(sum);
    }

    vector<double> output(10);


    for (int i = 0; i < 10; i++)
    {
        double sum = biasOutput[i];


        for (int j = 0; j < 64; j++)
        {
            sum +=
                weightsHidden2Output[i][j]
                * hidden2[j];
        }


        output[i] = sum;
    }


    return output;
}

vector<double> NeuralNetwork::predict(
    const vector<double>& input
)
{
    vector<double> hidden1;
    vector<double> hidden2;


    vector<double> output =
        forward(
            input,
            hidden1,
            hidden2
        );


    return softmax(output);
}


void NeuralNetwork::train(
    const vector<double>& input,
    int label,
    double learningRate
)
{
    vector<double> hidden1;
    vector<double> hidden2;


    vector<double> output =
        forward(
            input,
            hidden1,
            hidden2
        );


    vector<double> probabilities =
        softmax(output);

    vector<double> outputGradient(10);


    for (int i = 0; i < 10; i++)
    {
        double target =
            (i == label) ? 1.0 : 0.0;


        outputGradient[i] =
            probabilities[i] - target;
    }

    vector<double> hidden2Gradient(64);


    for (int j = 0; j < 64; j++)
    {
        double gradient = 0.0;


        for (int i = 0; i < 10; i++)
        {
            gradient +=
                outputGradient[i]
                * weightsHidden2Output[i][j];
        }


        hidden2Gradient[j] =
            gradient
            * reluDerivative(hidden2[j]);
    }

    vector<double> hidden1Gradient(128);


    for (int j = 0; j < 128; j++)
    {
        double gradient = 0.0;


        for (int i = 0; i < 64; i++)
        {
            gradient +=
                hidden2Gradient[i]
                * weightsHidden1Hidden2[i][j];
        }


        hidden1Gradient[j] =
            gradient
            * reluDerivative(hidden1[j]);
    }

    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 64; j++)
        {
            weightsHidden2Output[i][j] -=
                learningRate
                * outputGradient[i]
                * hidden2[j];
        }


        biasOutput[i] -=
            learningRate
            * outputGradient[i];
    }

    for (int i = 0; i < 64; i++)
    {
        for (int j = 0; j < 128; j++)
        {
            weightsHidden1Hidden2[i][j] -=
                learningRate
                * hidden2Gradient[i]
                * hidden1[j];
        }


        biasHidden2[i] -=
            learningRate
            * hidden2Gradient[i];
    }

    for (int i = 0; i < 128; i++)
    {
        for (int j = 0; j < 784; j++)
        {
            weightsInputHidden1[i][j] -=
                learningRate
                * hidden1Gradient[i]
                * input[j];
        }


        biasHidden1[i] -=
            learningRate
            * hidden1Gradient[i];
    }
}


void NeuralNetwork::save(
    const string& filename
) const
{
    ofstream file(
        filename,
        ios::binary
    );


    if (!file)
    {
        throw runtime_error(
            "Cannot save model: " + filename
        );
    }


    for (const auto& neuron : weightsInputHidden1)
    {
        file.write(
            reinterpret_cast<const char*>(
                neuron.data()
            ),
            neuron.size() * sizeof(double)
        );
    }


    file.write(
        reinterpret_cast<const char*>(
            biasHidden1.data()
        ),
        biasHidden1.size() * sizeof(double)
    );


    for (const auto& neuron : weightsHidden1Hidden2)
    {
        file.write(
            reinterpret_cast<const char*>(
                neuron.data()
            ),
            neuron.size() * sizeof(double)
        );
    }


    file.write(
        reinterpret_cast<const char*>(
            biasHidden2.data()
        ),
        biasHidden2.size() * sizeof(double)
    );


    for (const auto& neuron : weightsHidden2Output)
    {
        file.write(
            reinterpret_cast<const char*>(
                neuron.data()
            ),
            neuron.size() * sizeof(double)
        );
    }


    file.write(
        reinterpret_cast<const char*>(
            biasOutput.data()
        ),
        biasOutput.size() * sizeof(double)
    );
}


void NeuralNetwork::load(
    const string& filename
)
{
    ifstream file(
        filename,
        ios::binary
    );


    if (!file)
    {
        throw runtime_error(
            "Cannot load model: " + filename
        );
    }


    for (auto& neuron : weightsInputHidden1)
    {
        file.read(
            reinterpret_cast<char*>(
                neuron.data()
            ),
            neuron.size() * sizeof(double)
        );
    }


    file.read(
        reinterpret_cast<char*>(
            biasHidden1.data()
        ),
        biasHidden1.size() * sizeof(double)
    );


    for (auto& neuron : weightsHidden1Hidden2)
    {
        file.read(
            reinterpret_cast<char*>(
                neuron.data()
            ),
            neuron.size() * sizeof(double)
        );
    }


    file.read(
        reinterpret_cast<char*>(
            biasHidden2.data()
        ),
        biasHidden2.size() * sizeof(double)
    );


    for (auto& neuron : weightsHidden2Output)
    {
        file.read(
            reinterpret_cast<char*>(
                neuron.data()
            ),
            neuron.size() * sizeof(double)
        );
    }


    file.read(
        reinterpret_cast<char*>(
            biasOutput.data()
        ),
        biasOutput.size() * sizeof(double)
    );
}