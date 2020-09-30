#include<omp.h>
#include<random>
#include<cmath>

#pragma once
//Random initializer for weights

double random_init(double x){

       return (double)(rand() % 10000 + 1)/10000-0.5;
}

//Sigmoid Activation function
#pragma omp declare simd
double sigmoid(double x){

    return 1/(1+exp(-x));
}

//ReLU Activation function
#pragma omp declare simd
double relu(double x){
    if(x>0)
      return x;
    else
      return (double)0;       
      
}

//Sigmoid Derivative
#pragma omp declare simd
double sigmoid_derivative(double x){

    double sig = sigmoid(x);
    return sig*(1-sig);
}

//ReLU Derivative
#pragma omp declare simd
double relu_derivative(double x){
    if(x>0)
      return (double)1;
    else
      return (double)0;
     
}