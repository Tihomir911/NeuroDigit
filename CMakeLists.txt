cmake_minimum_required(VERSION 3.20)

project(NeuroDigit)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


find_package(PkgConfig REQUIRED)

pkg_check_modules(HTTPLIB REQUIRED cpp-httplib)


add_executable(NeuroDigit
    backend/main.cpp
    backend/NeuralNetwork.cpp
    backend/Mnist.cpp
    backend/HttpServer.cpp
)


target_include_directories(NeuroDigit
    PRIVATE
    ${HTTPLIB_INCLUDE_DIRS}
)


target_link_directories(NeuroDigit
    PRIVATE
    ${HTTPLIB_LIBRARY_DIRS}
)


target_link_libraries(NeuroDigit
    PRIVATE
    ${HTTPLIB_LIBRARIES}
)