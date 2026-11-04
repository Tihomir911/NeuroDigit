
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

    // Train the network using one sample (SGD).
    void train(
        const vector<double>& input,
        int label,
        double learningRate
    );

    // Accumulate gradients for one training sample.
    void accumulateGradients(
        const vector<double>& input,
        int label
    );

    // Apply accumulated gradients using Adam.
    void updateAdam(
        double learningRate,
        int batchSize
    );

    // Reset accumulated gradients.
    void resetGradients();

    // Save and load model parameters.
    void save(
        const string& filename
    ) const;

    void load(
        const string& filename
    );

    // Visualization accessors.
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

    // Neural network parameters.
    vector<vector<double>> weightsInputHidden1;
    vector<double> biasHidden1;

    vector<vector<double>> weightsHidden1Hidden2;
    vector<double> biasHidden2;

    vector<vector<double>> weightsHidden2Output;
    vector<double> biasOutput;

    // Accumulated gradients.
    vector<vector<double>> gradInputHidden1;
    vector<double> gradBiasHidden1;

    vector<vector<double>> gradHidden1Hidden2;
    vector<double> gradBiasHidden2;

    vector<vector<double>> gradHidden2Output;
    vector<double> gradBiasOutput;

    // Adam first moments.
    vector<vector<double>> mInputHidden1;
    vector<double> mBiasHidden1;

    vector<vector<double>> mHidden1Hidden2;
    vector<double> mBiasHidden2;

    vector<vector<double>> mHidden2Output;
    vector<double> mBiasOutput;

    // Adam second moments.
    vector<vector<double>> vInputHidden1;
    vector<double> vBiasHidden1;

    vector<vector<double>> vHidden1Hidden2;
    vector<double> vBiasHidden2;

    vector<vector<double>> vHidden2Output;
    vector<double> vBiasOutput;

    // Optimizer state.
    unsigned long long adamStep = 0;
    int accumulatedSamples = 0;

    // Adam hyperparameters.
    const double beta1 = 0.9;
    const double beta2 = 0.999;
    const double epsilon = 1e-8;
};
