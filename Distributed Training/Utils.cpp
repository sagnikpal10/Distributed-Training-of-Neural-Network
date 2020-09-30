#pragma once
#include<mpi/mpi.h>

#define size_n sizeof(int)
#define model 10

#define g_size 10
#define l_size 5

#include "../Neural Networks/Network/training.cpp"

MPI_Datatype Network = MPI_INT;
MPI_Datatype Data = MPI_INT;
MPI_Datatype Updates = MPI_INT;


namespace NN{

          typedef int NeuralNetwork;

          NeuralNetwork init_Network(){return 0;}
          void createNetwork(int* arr,int size){ for(int i=0;i<size;i++)arr[i]=i; }     

          int get_Network_size(NeuralNetwork * N){ return 10;}

          void updateWeights(NeuralNetwork * NN,int *update){

               //update the weights

          }

          int Forward(int * model_nn, int* data){

              return 0; 
          }

          int * getGradients(int* updates,int * data,int * model_nn){

              return 0;
          }

          void Validate(NeuralNetwork* nn, int * data,int start_index){};
          

}

namespace Dataset{

          typedef int Matrix;

          void init_Dataset(int * arr,int size,string path){for(int i=0;i<size;i++)arr[i]=i;
                            
          }

}

namespace W {

      typedef int WeightUpdates;

}

namespace Loss{

      typedef int crossentropyloss;

}
