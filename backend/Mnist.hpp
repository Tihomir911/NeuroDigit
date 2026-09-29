#pragma once

#include <vector>
#include <string>

using namespace std;

class Mnist {
    
    public:

    vector<vector<double>> images;
    vector<int> labels;

    void loadImages(const string& filename);
    void loadLabels(const string& filename);

    int size() const;

};