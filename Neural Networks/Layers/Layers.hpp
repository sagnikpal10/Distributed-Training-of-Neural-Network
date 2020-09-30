/* C++ Header files to define the Layer Class */
#ifndef DEF_LAYERS
#define DEF_LAYERS

#include "../Matrix/Matrix.hpp"
#include<string>

#pragma once

class Layer{


      public:

      Matrix  W,b,Z,A,dZ,dA,dW,db;
      std::string activation;
      bool input;
      bool output;

      Layer(int input_shape,int num_hidden,std::string activation,bool input,bool output);
      void Summary();
};      
#endif

