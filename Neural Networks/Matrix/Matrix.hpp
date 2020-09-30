/* C++ Header file to define the Matrix Class with associated operations */

#ifndef DEF_MATRIX
#define DEF_MATRIX

#include<iostream>
#include<vector>

#pragma once

class Matrix
{

  public:
   
      Matrix();
      Matrix(int height,int width);
      void init(int height,int weight);
      void init(std::vector<std::vector<double>> const &array);

      //Function for scalar multiplication
      Matrix multiply(double const &value);
      //Function for transpose
      Matrix Transpose();

      //Function for addition
      Matrix add(Matrix const &m) const;
      Matrix add(double const &v) const;
      //Function for subtraction
      Matrix subtract(Matrix const &m) const;
      //Function for hadamard product
      Matrix multiply(Matrix const &m) const;
      //Function for element-wise division
      Matrix divide(Matrix const &m) const;
      //Function for dot product 
      Matrix dot(Matrix const &m) const;
      Matrix Transpose() const;
      
      //To apply a function to the matrix
      Matrix applyFunction(double (*function)(double)) const;
      int getheight(); 


      //operator to assign a matrix to another
      void operator = (const Matrix & M); 
      //Function to get the element sum of the matrix
      double getElementSum();
      //print the matrix
      void print();

       
      
  private:

      std::vector<std::vector<double>> array;
      int height;
      int width;    
};



#endif
