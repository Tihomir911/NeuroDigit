# NeuroDigit

**NeuroDigit** is a handwritten digit recognition application built from scratch in C++ using a multilayer perceptron (MLP).

Draw a digit in your browser and let the neural network recognize it. The application combines a C++ backend, an interactive web interface, and a trained neural network.

## Features

- Handwritten digit recognition (0–9)
- Interactive browser-based drawing canvas
- C++ neural network implemented from scratch
- Visualization of neural network weights
- Real-time predictions through an HTTP API
- Docker image with the trained model included
- Terminal interface with startup information

## Demo

The web interface is available at:

`http://localhost:8080`

## Quick Start with Docker

The easiest way to run NeuroDigit is with Docker.

### 1. Pull the image

```bash
docker pull tihomir288/neurodigit:latest
```

### 2. Run the container

```bash
docker run -d \
  --name neurodigit \
  -p 8080:8080 \
  tihomir288/neurodigit:latest
```

### 3. Open the application

Visit:

`http://localhost:8080`

### Container management

View application logs:

```bash
docker logs -f neurodigit
```

Stop the container:

```bash
docker stop neurodigit
```

Remove the container:

```bash
docker rm neurodigit
```

## Neural Network Architecture

NeuroDigit uses a multilayer perceptron with the following architecture:

```text
Input Layer    Hidden Layer 1    Hidden Layer 2    Output Layer

   784      →      128       →       64        →       10
```

- **Input:** 784 neurons representing a 28×28 grayscale image.
- **Hidden layers:** ReLU activation.
- **Output:** 10 neurons representing digits from 0 to 9.
- **Output activation:** Softmax.

The network performs forward propagation, loss calculation, and training without relying on machine learning frameworks.

## Model Performance

The trained model achieved **95.81% accuracy** on the 10,000-image MNIST test dataset.

| Metric | Result |
|---|---:|
| Test images | 10,000 |
| Correct predictions | 9,581 |
| Incorrect predictions | 419 |
| Accuracy | 95.81% |

The trained `model.bin` is included in the Docker image.

## Technologies

| Technology | Purpose |
|---|---|
| C++17 | Neural network and backend |
| HTML | Web interface structure |
| CSS | Interface styling |
| JavaScript | Drawing canvas and frontend logic |
| CMake | Build system |
| cpp-httplib | HTTP server |
| nlohmann/json | JSON processing |
| MNIST | Training and testing dataset |
| Docker | Application packaging |

## Building from Source

### Requirements

- C++17 compatible compiler
- CMake
- pkg-config
- cpp-httplib
- nlohmann-json

### Build

```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build
```

### Run the server

```bash
./build/NeuroDigit server
```

Open `http://localhost:8080` in your browser.

### Training and evaluation

The application also provides training and evaluation modes:

```bash
./build/NeuroDigit train
./build/NeuroDigit evaluate
```

The MNIST dataset must be available in the expected `data/mnist/` directory.

## Project Structure

```text
NeuroDigit/
├── backend/
│   ├── main.cpp
│   ├── NeuralNetwork.hpp
│   ├── NeuralNetwork.cpp
│   ├── Mnist.hpp
│   ├── Mnist.cpp
│   ├── HttpServer.cpp
│   ├── HttpServer.hpp
│   ├── TerminalUI.cpp
│   └── TerminalUI.hpp
│
├── frontend/
│   ├── index.html
│   ├── style.css
│   └── app.js
│
├── data/
│   └── mnist/
│
├── model.bin
├── CMakeLists.txt
├── Dockerfile
└── README.md
```

## About

NeuroDigit is an educational machine learning project focused on understanding how neural networks work internally.

The project explores neural network mathematics, weights, biases, activation functions, forward propagation, loss calculation, and model training.

It also demonstrates how to combine a C++ machine learning backend with a browser-based frontend and Docker deployment.
