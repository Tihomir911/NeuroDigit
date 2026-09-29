cmake_minimum_required(VERSION 3.20)

project(NeuroDigit)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(NeuroDigit
    backend/main.cpp
    backend/NeuralNetwork.cpp
    backend/Mnist.cpp
    backend/HttpServer.cpp
)