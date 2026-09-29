#include "NeuralNetwork.hpp"

#include <iostream>
#include <vector>

using namespace std;

int main(){

    NeuralNetwork network;

    vector<double> input(784, 0.0); 

    vector<double> probabilities = network.predict(input);

    cout << "predictions: " << endl;

    for (int i = 0; i < probabilities.size(); i++){

        cout << "Class " << i << ": " << probabilities[i] << endl;

    }

    return 0;

}