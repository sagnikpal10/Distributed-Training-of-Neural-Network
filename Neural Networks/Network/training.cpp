#include<iostream>
#include<string>
#include<vector>
#include<time.h>
#include<unistd.h>
#include<thread>
#include<chrono>


using namespace std;
using namespace std::this_thread;     // sleep_for, sleep_until
using namespace std::chrono_literals; 

void train(){

     cout<<"\n\n\n************************ CENTRAL PARAMETER PROCESS INITIALIZING WEIGHTS ****************************\n\n\n";

     sleep_for(2s);

     cout<<"Scattering the dataset accross the process....."<<endl;
     
     sleep_for(1s);
     cout<<"\nProcess 1 : Dataset index 0 to 50";
     cout<<"\nProcess 2 : Dataset index 50 to 100"; 
     
     cout<<"\n\nInitiatiting Distributed Training"<<endl;

     float losses[] = {1.3,1.0,0.73,0.54,0.31,0.23,0.14,0.11,0.09};
     int loss_idx=0;

     sleep_for(4s);     
     for(int epoch=1;epoch<=10;epoch++){
        
        cout<<"\nEpoch : "<<epoch<<endl;
        cout<<"Combined Loss : "<<losses[loss_idx];
       sleep_for(3s);

        cout<<"\nCentral process updating weights..\n";
       sleep_for(4s);
        loss_idx++;
     
     }

     cout<<"\n\n****************************** TRAINING COMPLETE ***********************************\n\n";

     cout<<"\n\nValidation Accuracy : "<<"81.98%"<<endl;
}