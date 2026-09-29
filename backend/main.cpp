/*#include "NeuralNetwork.hpp"

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

} */

#include "NeuralNetwork.hpp"
#include "Mnist.hpp"

#include <iostream>
#include <iomanip>

using namespace std;


int main()
{
    Mnist dataset;


    cout << "Loading MNIST..." << endl;


    dataset.loadImages(
        "data/mnist/train-images-idx3-ubyte"
    );

    dataset.loadLabels(
        "data/mnist/train-labels-idx1-ubyte"
    );


    cout << "Images: "
         << dataset.images.size()
         << endl;

    cout << "Labels: "
         << dataset.labels.size()
         << endl;


    NeuralNetwork network;


    const double learningRate = 0.01;


    cout << endl;
    cout << "Starting training..." << endl;
    cout << endl;


    for (int i = 0; i < 60000; i++)
    {
        network.train(
            dataset.images[i],
            dataset.labels[i],
            learningRate
        );


        if (i % 1000 == 0)
        {
            cout << "Training: "
                 << i
                 << " / 60000"
                 << endl;
        }
    }


    cout << endl;
    cout << "Training finished!" << endl;


    network.save("model.bin");


    cout << "Model saved to model.bin"
         << endl;


    return 0;
}