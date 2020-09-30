#pragma once
#include "Network.hpp"

void NeuralNetwork::add(Layer * layer){
     
     this->Layers.push_back(layer);

}

Matrix NeuralNetwork::feed_forward(Matrix X){

     Matrix Y,out;
     for(auto l:this->Layers){

         
         if(l->input==true){

            
            out  = l->W.dot(X);
            out  = l->b.add(out);
            l->Z = out;
            
            if(l->activation=="sigmoid"){
              out  = out.applyFunction(sigmoid);
              l->A = out;
              
            }
            else if(l->activation=="relu"){
              out  = out.applyFunction(relu);
              l->A = out;
              
            } 
         }

         else{

            
            out  = l->W.dot(out);
            out  = l->b.add(out);
            l->Z = out;
            
            if(l->activation=="sigmoid"){
              out  = out.applyFunction(sigmoid);
              l->A = out;
              
            }
            else if(l->activation=="relu"){
              out  = out.applyFunction(relu);
              l->A = out;
              
            } 


         }
        
        

     }

     Y = out;
     return Y;
}

