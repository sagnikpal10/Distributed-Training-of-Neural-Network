/*** Utilities for distributed training ***/

#pragma once

#include<mpi/mpi.h>
#include<string>
#include "../Neural Networks/Network/Network.cpp"
#include "../Neural Networks/Network/Train.cpp"

#include "../Neural Networks/Dataset/DatasetUtils.cpp"
#include "../Neural Networks/Dataset/Parser.cpp"
#include "Utils.cpp"


void CreateNetwork(NeuralNetwork  NN,int size){


   NN.add(new Layer(100,200,"relu",true,false));
   NN.add(new Layer(200,200,"relu",false,false));
   NN.add(new Layer(200,100,"relu",false,false));
   NN.add(new Layer(100,3,"sigmoid",false,true));

}

int get_Network_size(NeuralNetwork NN){

    int sizeNetwork = sizeof(NeuralNetwork);
    return sizeNetwork; 

}

void init_Dataset(Matrix &dataset,int size,char* path){

     Matrix dataset_matrix = parse_data(path);

     dataset = dataset_matrix;


}

struct WeightUpdates{

       Matrix dW[g_size];

};

double Forward(NeuralNetwork NN,Matrix data){

       Matrix out = NN.feed_forward(data);

       double loss = CrossEntropyLoss(data,out);

       return loss;

}

void getGradients(WeightUpdates updates,NeuralNetwork NN,Matrix out){

                  
     int num_layers = NN.Layers.size();

     int layer_index=0;
     
/***************************** BACK PROPAGATION OF THE LAST LAYER **********************************************/

     for(int i=num_layers-1;i>=0;i--){

        std::cout<<"\n\nLayer : "<<i+1<<"\n\n\n"; 

        if(NN.Layers[i]->output==true){

          
          
          int m = NN.Layers[i]->W.getheight();

          Matrix dA,dZ,dW,dA1;
          double db;

          dA = out.multiply(-1).divide(NN.Layers[i]->A).subtract(out.multiply(-1).add(1).divide(NN.Layers[i]->A.multiply(-1).add(1)));
          dZ = NN.Layers[i]->Z.applyFunction(sigmoid_derivative).multiply(dA);

          
          
          dZ.print();
          Matrix AT = NN.Layers[i-1]->A.Transpose();
          AT.print();

          
          dW = dZ.dot(NN.Layers[i-1]->A.Transpose()).multiply((double)1/m);
          
          
          
          db = (double)dZ.getElementSum()/m;

          dA1 = NN.Layers[i]->W.Transpose().dot(dZ);
          dA1.print();
          
          updates.dW[layer_index++] = dW;

          NN.Layers[i]->dA   = dA;
          
          NN.Layers[i]->dZ   = dZ;
          
          NN.Layers[i-1]->dA = dA1;
          
          
        }
        
/*********************************** BACKPROPAGATION OF THE INPUT LAYERS **************************************************************/        

        else if(NN.Layers[i]->input==true){

          std::cout<<"\n\nElse part called\n\n";

          int m = NN.Layers[i]->W.getheight();

          Matrix dA,dZ,dW;
          dA = NN.Layers[i]->dA;
          double db;

          dA.print();

         // dA = out.multiply(-1).divide(*NN.Layers[i]->A).subtract(out.multiply(-1).add(1).divide(NN.Layers[i]->A->multiply(-1).add(1)));
          
          dZ = NN.Layers[i]->Z.applyFunction(sigmoid_derivative).multiply(dA);
          dZ.print();

          std::cout<<"\n\nprint the weight update\n\n";
          //Matrix t = X.Transpose();
         // t.print();
          dW = NN.Layers[i]->W;
          //dW = dZ.dot(NN.Layers[i-1]->A.Transpose()).multiply((double)1/m);
          dW.print();

          db = (double)dZ.getElementSum()/m;
          std::cout<<db;

          updates.dW[layer_index++] = dW;

          //NN.Layers[i]->dA   = new Matrix(dA);
          NN.Layers[i]->dZ   = dZ;
          
          
         
 
        }

        /******************************* BACK PROPAGATION FOR REST OF THE LAYERS **********************************************/
        else{

             std::cout<<"\n\nElse part called\n\n";

          int m = NN.Layers[i]->W.getheight();

          Matrix dA,dZ,dW,dA1;
          dA = NN.Layers[i]->dA;
          double db;

          dA.print();

         // dA = out.multiply(-1).divide(*NN.Layers[i]->A).subtract(out.multiply(-1).add(1).divide(NN.Layers[i]->A->multiply(-1).add(1)));
          
          dZ = NN.Layers[i]->Z.applyFunction(sigmoid_derivative).multiply(dA);
          dZ.print();

          std::cout<<"\n\nprint the weight update\n\n";
          Matrix t = NN.Layers[i-1]->A.Transpose();
          t.print();
          dW = NN.Layers[i]->W;
          //dZ.dot(NN.Layers[i-1]->A.Transpose()).multiply((double)1/m).print();
          dW.print();

          db = (double)dZ.getElementSum()/m;
          std::cout<<db;

          dA1 = NN.Layers[i]->W.Transpose().dot(dZ);
          dA1.print();
          
          updates.dW[layer_index++] = dW;

          //NN.Layers[i]->dA   = new Matrix(dA);
          NN.Layers[i]->dZ   = dZ;
          NN.Layers[i-1]->dA = dA1;
          
        
        }  
        
    } 




}

void updateWeights(NeuralNetwork & NN,WeightUpdates updates){


      
       int num_layers = NN.Layers.size();

       for(int i=0;i<num_layers;i++){

          NN.Layers[i]->W = NN.Layers[i]->W.subtract(updates.dW[i].multiply(0.01));


       }

}

void Validate(NeuralNetwork &NN,Matrix* Dataset,int start_index){

     int correct;  
     for(int index=start_index;index<75;index++){

         Matrix Out = NN.feed_forward(Dataset[index]);
         if(isCorrect(Out,Dataset[index]))
            correct++;
          }


     double accuracy = (correct)/(75-start_index)*100;
     cout<<"\n\nValidation Accuracy : "<<accuracy<<endl;
}    










 




