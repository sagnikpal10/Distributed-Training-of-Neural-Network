#include<iostream>
#include<omp.h>

using namespace std;



int main(){

    omp_set_num_threads(4);

    int t;
    t = omp_get_thread_num();

    #pragma omp parallel
    {

        int x;
        x = omp_get_num_threads();
        #pragma omp master
        t+=x;


    }
    
    cout<<t; 


     return 0;

}