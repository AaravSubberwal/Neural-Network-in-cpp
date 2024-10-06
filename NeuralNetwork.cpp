
/***************************************************************************************************
Author: Aarav Subberwal
Date:

Work in progress
-Weights and biases are not yet initialized
-project will have 2 cpp files one for training and one for testing and checking accuracy
-one for testing will read weights and biases from a file
***************************************************************************************************/
#include <iostream>
#include <cmath>
#include <vector>
#include "Read_Data.cpp"
using namespace std;

class node
{
public:
    double bias, value;     // value must be calculated using sigmoid function
    vector<double> weights; // gotta randomly set them and check their domain
}; // maybe read em from another file

class layer
{
public:
    layer(int size) : nodes(size) {}

private:
    std::vector<node> nodes;

public:
    vector<node> getNodes()
    {
        return nodes;
    }
};

double dot(vector<double> v1, vector<double> v2)
{
    double result = 0;
    for (int i = 0; i < v1.size(); i++)
    {
        result += v1[i] * v2[i]; // optimize this somehow
    }
    return result;
}

double sigmoid(double n)
{
    return 1 / (1 + exp(-n));
}

int main()
{
    std::vector<MNISTImage> dataset = load_mnist("train-images-idx3-ubyte", "train-labels-idx1-ubyte");
    
    vector<double> input_layer(784); // each image is 28*28 pixel array
    layer first_layer(16);          
    layer second_layer(16);
    layer output_layer(10);
    vector<layer> NN = {first_layer, second_layer, output_layer};
    // initialize the weights here, 12960 weights
    //definately read em from a file
    


    for (int i = 0; i < dataset.size(); i++) // loop iterates over the dataset over every image
    {                                        // 784
        for (int j = 0; j < 784; j++)
        {
            input_layer[j] = static_cast<double>(dataset[i].pixels[j]);
        }
        // now the input layer is initialized

        for (node selected_node : first_layer.getNodes())
        {
            selected_node.value = sigmoid(dot(selected_node.weights, input_layer) + selected_node.bias);
        } // first layer values done

        vector<double> l1(16);
        for (int j = 0; j < 16; j++) // i converted them into a double array to pass into the dot product function
        {
            l1[j] = (first_layer.getNodes())[j].value;
        }
        for (node selected_node : second_layer.getNodes())
        {

            selected_node.value = sigmoid(dot(selected_node.weights, l1) + selected_node.bias);
        } // second layer values done

        vector<double> l2(16);
        for (int j = 0; j < 16; j++)
        {
            l2[j] = (second_layer.getNodes())[j].value;
        }
        for (node selected_node : output_layer.getNodes())
        {

            selected_node.value = sigmoid(dot(selected_node.weights, l2) + selected_node.bias);
        } // output layer values done

        vector<double> l3(10);
        for (int j = 0; j < 10; j++)
        {
            l3[j] = (output_layer.getNodes())[j].value;
        }
        //calculated mean square error
    }
}