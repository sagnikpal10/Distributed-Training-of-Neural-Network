#include "Matrix.hpp"
#include <assert.h>
#include <sstream>
#include <omp.h>

#pragma once

Matrix::Matrix(){}

Matrix::Matrix(int height,int width){

      this->height = height;
      this->width  = width;
      this->array  = std::vector<std::vector<double>>(height,std::vector<double>(width,0.0));


}

void Matrix::init(int height, int width){

      this->height = height;
      this->width  = width;
      this->array  = std::vector<std::vector<double>>(height,std::vector<double>(width,0.0));

}

void Matrix::init(std::vector<std::vector<double>> const &array){

      
      assert(this->array.size()!=0);
      this->height = array.size();
      this->width  = array[0].size();
      this->array  = array;

}

void Matrix::operator = (const Matrix & M){

      assert(M.array.size()!=0);
      this->height = M.array.size();
      this->width  = M.array[0].size();
      this->array  = M.array;



}

Matrix Matrix::multiply(double const &value)
{

       Matrix result(height,width);
       int i,j;

       #pragma omp parallel for
       
       for(i=0;i<height;i++){
           #pragma omp simd
           for(j=0;j<width;j++){
               result.array[i][j] = array[i][j]*value;
           }
       }
       

       return result;
}

Matrix Matrix::Transpose(){

       Matrix result(width,height);
       int i,j;

       #pragma omp parallel for
       
       for(i=0;i<width;i++){
           #pragma omp simd
           for(j=0;j<height;j++){
               result.array[i][j] = this->array[j][i];
           }
       }
       

       return result;
} 





Matrix Matrix::add(Matrix const &m) const
{

       assert(height==m.height && width==m.width);

       Matrix result(height,width);
       int i,j;

       #pragma omp parallel for
       
       for(i=0;i<height;i++){
           #pragma omp simd
           for(j=0;j<width;j++)
               result.array[i][j] = array[i][j]+m.array[i][j];
            }
       
        return result;  
}

Matrix Matrix::add(double const &v) const{
 
       Matrix result(height,width);
       int i,j;

       #pragma omp parallel for
       
       for(i=0;i<height;i++){
           #pragma omp simd
           for(j=0;j<width;j++)
               result.array[i][j] = array[i][j]+v;
            }
       
        return result;  


}

Matrix Matrix::subtract(Matrix const &m) const
{

       assert(height==m.height && width==m.width);

       Matrix result(height,width);
       int i,j;

       #pragma omp parallel for
       
       for(i=0;i<height;i++){
           #pragma omp simd
           for(j=0;j<width;j++)
               result.array[i][j] = array[i][j]-m.array[i][j];
       }
       

        return result;  
}

Matrix Matrix::multiply(Matrix const &m) const
{

       assert(height==m.height && width==m.width);

       Matrix result(height,width);
       int i,j;

       #pragma omp parallel for
       
       for(i=0;i<height;i++){
           #pragma omp simd
           for(j=0;j<width;j++)
               result.array[i][j] = array[i][j]*m.array[i][j];
       }
       

        return result;  
}

Matrix Matrix::divide(Matrix const &m) const{

       assert(height==m.height && width==m.width);

       Matrix result(height,width);
       int i,j;

       #pragma omp parallel for
       
       for(i=0;i<height;i++){
           #pragma omp simd
           for(j=0;j<width;j++)
               result.array[i][j] = array[i][j]/m.array[i][j];
       }
       

        return result;   



}

Matrix Matrix::dot(Matrix const &m) const
{
       
       
    

       assert(width==m.height);

       int i,j,h,mwidth = m.width;
       double w = 0;

       Matrix result(height,mwidth);

       #pragma omp parallel for private(i,j,h)
       for(i=0;i<height;i++){
           for(h=0;h<width;h++){
               #pragma omp vector aligned
               for(j=0;j<mwidth;j++){
                   w += array[i][h] * m.array[h][j];
               }
               result.array[i][j] = w;
               w = 0;
           }
       }

       return result;
}

Matrix Matrix::applyFunction(double (*function)(double)) const{


       Matrix result(height,width);
       int i,j;

       #pragma omp parallel for private(i,j)
       for(i=0;i<height;i++){
           #pragma omp simd
           for(j=0;j<width;j++){
               result.array[i][j] = (*function)(array[i][j]);
           }
       }

       return result;  

}

void Matrix::print(){

    
     std::cout<<"\nHeight = "<<height<<"   Width = "<<width<<"\n";

     for(int i=0;i<this->height;i++){
         for(int j=0;j<this->width;j++){

            std::cout<<this->array[i][j]<<" ";   

         }
         std::cout<<std::endl;
     }


}

int Matrix::getheight(){return height;}

double Matrix::getElementSum(){
    
    double sum = 0;
    #pragma omp parallel reduction(+:sum)
    for(int i=0;i<this->height;i++){
         for(int j=0;j<this->width;j++){

            sum+=this->array[i][j];   

         }
        
     }

     return sum;


}
