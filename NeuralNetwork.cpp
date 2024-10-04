
/***************************************************************************************************
Author: Aarav Subberwal
Date:

Work in progress

***************************************************************************************************/
#include <iostream>
#include <cmath>
#include <vector>
#include "Read_Data.cpp"
using namespace std;

class node
{
public:
    double bias, value;     //value must be calculated using sigmoid function
    vector<double> weights;     //gotta randomly set them and check their domain
};                                  //maybe read em from another file

class layer {
public:
    layer(int size) : nodes(size) {}

private:
    std::vector<node> nodes;
public:
    vector<node> getNodes(){
        return nodes;
    }
};                                

double dot(vector<double> v1,vector<double> v2){
    double result=0;
    for(int i=0;i<v1.size();i++){
        result+=v1[i]*v2[i];
    }
    return result;
}

vector<double> input_layer(784);  //each image is 28*28 pixel array
layer first_layer(16);      //global variables might be a problem
layer second_layer(16);     
layer output_layer(10);
vector<layer> NN = {first_layer, second_layer, output_layer};

int main()
{
    std::vector<MNISTImage> dataset = load_mnist("train-images-idx3-ubyte", "train-labels-idx1-ubyte");

    for (int i = 0; i < dataset.size(); i++) // loop iterates over the dataset over every image
    {                                        // 784
        for (int j = 0; j < 784; j++)
        { 
            input_layer[j] = static_cast<double>(dataset[i].pixels[j]);
        }
        // now the input layer is initialized

        // now actually fucking make the NN work
    }
}