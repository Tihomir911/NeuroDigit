#pragma once

#include <vector>
#include <string>

using namespace std;

class NeuralNetwork
{
public:

    NeuralNetwork();

    vector<double> predict(
        const vector<double>& input
    );

    void train(
        const vector<double>& input,
        int label,
        double learningRate
    );

    void save(
        const string& filename
    ) const;

    void load(
        const string& filename
    );

private:

    double relu(double value);

    double reluDerivative(double value);

    vector<double> softmax(
        const vector<double>& input
    );

    vector<double> forward(
        const vector<double>& input,
        vector<double>& hidden1,
        vector<double>& hidden2
    );

    vector<vector<double>> weightsInputHidden1;
    vector<double> biasHidden1;

    vector<vector<double>> weightsHidden1Hidden2;
    vector<double> biasHidden2;

    vector<vector<double>> weightsHidden2Output;
    vector<double> biasOutput;
};