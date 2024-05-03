#pragma once

#include <vector>
#include <string>
#include "Vector3.cpp"

using namespace std;

class Mesh {
    public:
        Mesh() {};
        Mesh(vector<string> obj);
        vector<char> header;
        vector<Vector3> data;
};

Mesh::Mesh(vector<string> obj) {
    for (string str : obj) {
        vector<string> tokens;
        istringstream iss(str);
        string token;
        while (getline(iss, token, ',')) {
            tokens.push_back(token);
        }
        // Doesnt allow for obj data with more or less than 3 values
        if (tokens.size() != 4) {
            data.push_back(Vector3());
            header.push_back('_');
            continue;
        }
        data.push_back(Vector3(stof(tokens.at(1)), stof(tokens.at(2)), stof(tokens.at(3))));
        header.push_back(str[0]);
    }
}