# NeuroDigit

NeuroDigit is a small handwritten digit recognition project built from scratch in C++.

The project uses a multilayer perceptron (MLP) trained on the MNIST dataset. Users can draw a digit directly in the browser, send the image to the C++ backend, and receive the neural network's prediction.

The interface features a dark visual style, an interactive drawing canvas, prediction results, and a visualization of the neural network.

## Architecture

The neural network uses the following architecture:

`784 → 128 → 64 → 10`

The 784 input neurons represent the pixels of a 28×28 image.

The hidden layers use the ReLU activation function, while the output layer uses Softmax to produce probabilities for the ten possible digits from 0 to 9.

The neural network and backend are written in C++, while the user interface is built with HTML, CSS, and JavaScript.

## Technologies

C++ is used for the neural network, MNIST processing, and backend API.

HTML, CSS, and JavaScript are used for the frontend and drawing interface.

CMake is used to build the C++ backend.

MNIST is used as the training and testing dataset.

## Project Structure

```text
NeuroDigit/
├── backend/
│   ├── main.cpp
│   ├── NeuralNetwork.hpp
│   ├── NeuralNetwork.cpp
│   ├── Mnist.hpp
│   └── Mnist.cpp
│
├── frontend/
│   ├── index.html
│   ├── style.css
│   └── app.js
│
├── data/
│   └── mnist/
│
├── CMakeLists.txt
└── README.md
```

## Building

NeuroDigit requires a C++ compiler and CMake.

The MNIST dataset should be placed inside:

```text
data/mnist/
```

Build the project using CMake:

```bash
mkdir build
cd build
cmake ..
cmake --build .
```

After building, start the C++ backend and open the frontend in a browser.

## About

NeuroDigit is primarily an educational project focused on understanding how a neural network works internally.

Instead of relying on machine learning frameworks, the core neural network is implemented from scratch. This makes it possible to explore concepts such as weights, biases, activation functions, forward propagation, loss calculation, and training in a practical way.

The project also combines several areas of software development: C++, neural network mathematics, HTTP backend development, and a JavaScript-based frontend.