
#pragma once

#include <vector>
#include <string>

using namespace std;
struct PredictionTrace
{
    vector<double> input;
    vector<double> hidden1;
    vector<double> hidden2;
    vector<double> logits;
    vector<double> probabilities;
};
class NeuralNetwork
{
public:

    NeuralNetwork();

    vector<double> predict(
        const vector<double>& input
    );

    PredictionTrace predictDetailed(
        const vector<double>& input
    );

    void train(
        const vector<double>& input,
        int label,
        double learningRate
    );

    void accumulateGradients(
        const vector<double>& input,
        int label
    );

    void updateAdam(
        double learningRate,
        int batchSize
    );

    void resetGradients();

    void save(
        const string& filename
    ) const;

    void load(
        const string& filename
    );

    const vector<vector<double>>&
    weightsInputHidden1ForVisualization() const;

    const vector<vector<double>>&
    weightsHidden1Hidden2ForVisualization() const;

    const vector<vector<double>>&
    weightsHidden2OutputForVisualization() const;

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

    vector<vector<double>> gradInputHidden1;
    vector<double> gradBiasHidden1;

    vector<vector<double>> gradHidden1Hidden2;
    vector<double> gradBiasHidden2;

    vector<vector<double>> gradHidden2Output;
    vector<double> gradBiasOutput;
    
    vector<vector<double>> mInputHidden1;
    vector<double> mBiasHidden1;

    vector<vector<double>> mHidden1Hidden2;
    vector<double> mBiasHidden2;

    vector<vector<double>> mHidden2Output;
    vector<double> mBiasOutput;

    vector<vector<double>> vInputHidden1;
    vector<double> vBiasHidden1;

    vector<vector<double>> vHidden1Hidden2;
    vector<double> vBiasHidden2;

    vector<vector<double>> vHidden2Output;
    vector<double> vBiasOutput;

    unsigned long long adamStep = 0;
    int accumulatedSamples = 0;

    const double beta1 = 0.9;
    const double beta2 = 0.999;
    const double epsilon = 1e-8;
};
