#ifndef DEF_NETWORK
#define DEF_NETWORK

#include "../Layers/Layers.cpp"
#include "../Matrix/Matrix.cpp"
#include "../Activations/Activations.cpp"

#pragma once


class NeuralNetwork{
      
      public:
         
         
         std::vector<Layer *> Layers;
         
         //Function to add layers to the network
         void add(Layer * layer);

         //Function to forward propagate
         Matrix feed_forward(Matrix X);
          





};
#endif