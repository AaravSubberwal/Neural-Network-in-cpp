#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

class node
{
public:
    double bias, value;
    vector<double> weights;
};

class layer
{
public:
    vector<node> nodes;
};

layer input_layer;
layer first_layer;
layer second_layer;
layer output_layer;
vector<layer> NN = {input_layer, first_layer, second_layer, output_layer};

int main()
{
}