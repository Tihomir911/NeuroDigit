#pragma once

#include <vector>
#include <string>

using namespace std;

class NeuralNetwork
{
    public:
        NeuralNetwork();
    
        vector<double> predict(const vector<double>& input);   

        void train(
            const vector<double>& input,
            const vector<double>& target,
            double learningRate
        );

        void save(const string& filename) const;
        void load(const string& filename);
    
    private:
        
        vector<vector<double>> weightMatrix;
        vector<double> biasHidden1;

        vector<vector<double>> weightsHidden1Hidden2;
        vector<double> biasHidden2;

        vector<vector<double>> weightsHidden2Output;
        vector<double> biasOutput;

};