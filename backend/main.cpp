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

using namespace std;

int main()
{
    Mnist dataset;

    dataset.loadImages(
        "data/mnist/train-images.idx3-ubyte"
    );

    dataset.loadLabels(
        "data/mnist/train-labels.idx1-ubyte"
    );

    cout << "Images: "
         << dataset.images.size()
         << endl;

    cout << "Labels: "
         << dataset.labels.size()
         << endl;

    cout << "First label: "
         << dataset.labels[0]
         << endl;

    cout << "First image pixels:" << endl;

    for (int i = 0; i < 20; i++)
    {
        cout << dataset.images[0][i] << " ";
    }

    cout << endl;

    return 0;
}