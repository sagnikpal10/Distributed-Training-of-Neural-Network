#include "Layers.hpp"
#include <iostream>
#include "../Activations/Activations.cpp"

#pragma once

Layer::Layer(int input_shape,int num_hidden,std::string activation,bool input,bool output){

      
       this->activation = activation;
       this->input  = input;
       this->output = output;
       
       W.init(num_hidden,input_shape);
       b.init(num_hidden,1);

       //Random initialisation of the weights (Bias is already zero initialized)
       W = W.applyFunction(random_init);
       
       
}

void Layer::Summary()
{

  //TODO : Summary of the layer

}