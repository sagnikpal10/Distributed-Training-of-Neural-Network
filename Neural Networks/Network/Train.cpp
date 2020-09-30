#include "Network.cpp"
#pragma once


void BackPropagate(NeuralNetwork &NN,Matrix &out,Matrix &X,double lr){

     //The backpropagation is written with respect to CrossEntropy loss as required in the application.

     int num_layers = NN.Layers.size();
     
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
          
          
          NN.Layers[i]->dA   = dA;
          
          NN.Layers[i]->dZ   = dZ;
          
          NN.Layers[i-1]->dA = dA1;
          
          
          //Update the weights
          NN.Layers[i]->W  = NN.Layers[i]->W.subtract(dW.multiply(lr));
          

          //Update the bias
          NN.Layers[i]->b  = NN.Layers[i]->b.add((double)-1*lr*db);
          

          //NN.Layers[i]->W->print();
          //NN.Layers[i]->b->print();
          
          
          
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
          Matrix t = X.Transpose();
          t.print();
          dW = NN.Layers[i]->W;
          //dW = dZ.dot(NN.Layers[i-1]->A.Transpose()).multiply((double)1/m);
          dW.print();

          db = (double)dZ.getElementSum()/m;
          std::cout<<db;

          

          //NN.Layers[i]->dA   = new Matrix(dA);
          NN.Layers[i]->dZ   = dZ;
          
          
          //Update the weights
          NN.Layers[i]->W  = NN.Layers[i]->W.subtract(dW.multiply(lr));
          NN.Layers[i]->W.print();

          //Update the bias
          NN.Layers[i]->b  = NN.Layers[i]->b.add((double)-1*lr*db);
          NN.Layers[i]->b.print();
 
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

          //NN.Layers[i]->dA   = new Matrix(dA);
          NN.Layers[i]->dZ   = dZ;
          NN.Layers[i-1]->dA = dA1;
          
          //Update the weights
          NN.Layers[i]->W  = NN.Layers[i]->W.subtract(dW.multiply(lr));
          NN.Layers[i]->W.print();

          //Update the bias
          NN.Layers[i]->b  = NN.Layers[i]->b.add((double)-1*lr*db);
          NN.Layers[i]->b.print();
 
        }  
        
    } 
    
}

double CrossEntropyLoss(const Matrix &Y,const Matrix &Y_hat){

       //Implement Cross entropy loss         



}

bool isCorrect(Matrix out1,Matrix out2){

     if(out1.getElementSum()==out2.getElementSum()){
       return true;
     }
      
      return false;

}

