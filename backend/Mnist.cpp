#include "Mnist.hpp"

#include <fstream>
#include <stdexcept>
#include <cstdint>

using namespace std;

uint32_t readBigEndian(ifstream& file) {
    
    uint8_t bytes[4];

    file.read(
        reinterpret_cast<char*>(bytes),
        4
    );

    return
        (static_cast<uint32_t>(bytes[0]) << 24) |
        (static_cast<uint32_t>(bytes[1]) << 16) |
        (static_cast<uint32_t>(bytes[2]) << 8)  |
        static_cast<uint32_t>(bytes[3]);

}

void Mnist::loadImages(
    const string& filename
)
{
    ifstream file(
        filename,
        ios::binary
    );

    if (!file){
        throw runtime_error(
            "Cannot open MNIST image file: " + filename
        );
    }

    uint32_t magicNumber = readBigEndian(file);
    uint32_t imageCount = readBigEndian(file);
    uint32_t rows = readBigEndian(file);
    uint32_t colums = readBigEndian(file);

    if (magicNumber != 2051){
        throw runtime_error(
            "Invalid MNIST image file"
        );
    }

    if (rows !=  28 || colums != 28){
        throw runtime_error(
            "MNIST images must be 28x28"
        );
    }

    images.resize(imageCount);

    for (uint32_t i =0; i < imageCount; i++){
        
        images[i].resize(784);
        
        for (int j = 0; j < 784; j++){

            uint8_t pixel;

            file.read(
                reinterpret_cast<char*>(&pixel),
                1
            );

            images[i][j] =
                static_cast<double>(pixel) / 256.0;
            
        }
    }
}

void Mnist::loadLabels(
    const string& filename
)
{
    ifstream file(
        filename,
        ios::binary
    );
    if (!file){
        throw runtime_error(
            "Cannot open MNIST label file:" + filename
        );
    }

    uint32_t magicNumber = readBigEndian(file);
    uint32_t labelCount = readBigEndian(file);

    if (magicNumber != 2049){
        throw runtime_error(
            "Invalid MNIST label file"
        );
    }

    labels.resize(labelCount);

    for (uint32_t i = 0; i < labelCount; i++){
        uint8_t label;

        file.read(
            reinterpret_cast<char*>(&label),
            1
        );

        labels[i] = static_cast<int>(label);
    }
}

int Mnist::size() const {

    return images.size();
}
