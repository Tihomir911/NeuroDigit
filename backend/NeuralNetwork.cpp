#include "NeuralNetwork.hpp"

#include <cmath>
#include <random>
#include <fstream>
#include <stdexcept>

NeuralNetwork::NeuralNetwork()
{
    // Network architecture:
    // 784 -> 128 -> 64 -> 10

    weightsInputHidden1.resize(128, std::vector<double>(784)); // create a 128x784 matrix  // 128 sicret x 784 input
    biasHidden1.resize(128);

    weightsHidden1Hidden2.resize(64, std::vector<double>(128)); 
    biasHidden2.resize(64);

    weightsHidden2Output.resize(10, std::vector<double>(64));
    biasOutput.resize(10);
}