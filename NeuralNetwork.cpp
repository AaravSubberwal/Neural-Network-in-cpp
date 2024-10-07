
/***************************************************************************************************
Author: Aarav Subberwal
Date:

Work in progress
***************************************************************************************************/
#include <iostream>
#include <cmath>
#include <vector>
#include <cstdlib>
#include "Read_Data.cpp"
using namespace std;

class node
{
public:
    double bias, value;     
    vector<double> weights; 
}; 

double dot(vector<double> v1, vector<node> v2)
{
    double result = 0;
    if (v1.size() == v2.size())
    {
        for (int i = 0; i < v1.size(); i++)
        {
            result += v1[i] * v2[i].value; // optimize this somehow
        }
        return result;
    }
    else
    {
        cout << "vector size equal nhi hai chuutiye";
        return 0;
    }
}

double sigmoid(double n)
{
    return 1 / (1 + exp(-n));
}
double relu(double n)
{
    return (n > 0) ? n : 0;
}

int main()
{
    //std::vector<MNISTImage> dataset = load_mnist("train-images-idx3-ubyte", "train-labels-idx1-ubyte");

    vector<node> input_layer(784); // each image is 28*28 pixel array
    vector<node> first_layer(16);
    vector<node> second_layer(16);
    vector<node> output_layer(10);

    std::ifstream inFile("InitialWeightsBiases.bin", std::ios::binary);
    if (!inFile)
    {
        std::cerr << "tu chutiya hai (file read)" << std::endl;
        return 1;
    }
    std::vector<double> buffer(784);
    for (int i = 0; i < 16; i++)
    { // first layer nodes weights and biases initialized
        inFile.read(reinterpret_cast<char *>(buffer.data()), 784 * sizeof(double));
        first_layer[i].weights = buffer;
        first_layer[i].bias = ((rand() / (RAND_MAX + 1.0)) - 0.5)*0;
    }
    buffer.resize(16);
    for (int i = 0; i < 16; i++)
    { // second layer nodes weights and biases initialized
        inFile.read(reinterpret_cast<char *>(buffer.data()), 16 * sizeof(double));
        second_layer[i].weights = buffer;
        second_layer[i].bias = ((rand() / (RAND_MAX + 1.0)) - 0.5)*0;
    }
    for (int i = 0; i < 10; i++)
    { // output layer nodes weights and biases initialized
        inFile.read(reinterpret_cast<char *>(buffer.data()), 16 * sizeof(double));
        output_layer[i].weights = buffer;
        output_layer[i].bias = ((rand() / (RAND_MAX + 1.0)) - 0.5)*0;
    }
    inFile.close();
    //for (int i = 0; i < dataset.size(); i++)
     // loop iterates over the dataset over every image

        for (int j = 0; j < 784; j++)
        {
            input_layer[j].value = 0.3;
        }
        //static_cast<double>(dataset[i].pixels[j])
        // now the input layer is initialized

        for (int j = 0; j < 16; j++)
        {
            first_layer[j].value = relu((dot(first_layer[j].weights, input_layer)) + first_layer[j].bias);
            cout << first_layer[j].value << "\n";
        } // first layer values done
        cout << "\n\n";
        for (node &selected_node : second_layer)
        {
            selected_node.value = relu(dot(selected_node.weights, first_layer) + selected_node.bias);
            cout << selected_node.value << '\n';
        } // second layer values done
        cout << "\n\n";
        for (node &selected_node : output_layer)
        {
            selected_node.value = sigmoid(dot(selected_node.weights, second_layer) + selected_node.bias);
            cout << selected_node.value << '\n';
        } // output layer values done
    
    // calculated mean square error
    return 0;
}