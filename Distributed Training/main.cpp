/**********    Driver module to initialize the distributed training   *****************/
/* @author: Abhishek Jha 
*/

#include "DistributedTrainingUtils.cpp"


using namespace std;


int main(int argc,char** argv){


    /** Inititalization **/

    //Neural Network Object
    NN::NeuralNetwork MainModel[model],LocalModel[model];

    //Dataset Object
    char* DATASET_PATH = "../rs126";
    Dataset::Matrix GlobalDataset[g_size],LocalDataset[l_size];

    W::WeightUpdates globalUpdates[model],localUpdates[model];
    Loss::crossentropyloss localLoss,GlobalLoss;
    

    //MPI Environment Variables
    int len;
    MPI_Win win;
    int rank,size;
    char name[MPI_MAX_PROCESSOR_NAME];
    MPI_Aint size_model;






    MPI_Init(&argc,&argv);

    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&size);
    MPI_Get_processor_name(name, &len);


    /* Initialize all the required modules including the Neural Network and Dataset */
     
   
         

         //initialize the neural network within the shared memory
         //cout<<"\nProcess" <<rank<<" running on "<<name<<" initializing the local Neural Network\n ";

         
         //MainModel  = NN::init_Network();
         size_model = NN::get_Network_size(MainModel); 

         //Allocate the shared memory for the network
         MPI_Win_create(MainModel,size_model,size_n,MPI_INFO_NULL,MPI_COMM_WORLD,&win);
         NN::createNetwork(MainModel,model);
         NN::createNetwork(LocalModel,model);

         //cout<<"\n\n--------- Network Summary ---------";

    
    MPI_Win_fence(0,win);
    MPI_Barrier(MPI_COMM_WORLD); 
    //The distribution process must be initiated after the mother process completes

    if(rank==0){

       cout<<"\n\n\n\n************************ CENTRAL PARAMETER SERVER INITIALIZING WEIGHTS ***********************\n\n\n\n";
        
        
        train(); 
        MPI_Get(&LocalModel[0],size_model,Network,size-1,0,size_model,Network,win);
        MPI_Win_fence(0,win); 
        
        MPI_Put(&LocalModel[0],size_model,Network,0,0,size_model,Network,win);
        MPI_Win_fence(0,win); 

        MPI_Barrier(MPI_COMM_WORLD);

        //initilaize the global dataset
        Dataset::init_Dataset(GlobalDataset,g_size,DATASET_PATH);

        //Scatter the Dataset
        MPI_Scatter(GlobalDataset,g_size,Data,LocalDataset,l_size,Data,0,MPI_COMM_WORLD);

        MPI_Barrier(MPI_COMM_WORLD);

        //get the weight updates and

        
       for(int epoch=0;epoch<10;epoch++){

        MPI_Reduce(localUpdates,globalUpdates,model,Updates,MPI_SUM,0,MPI_COMM_WORLD);

        NN::updateWeights(LocalModel,globalUpdates);

        MPI_Reduce(&localLoss,&GlobalLoss,1,MPI_DOUBLE,MPI_SUM,0,MPI_COMM_WORLD);

        cout<<"Epoch : "<<epoch; 
        cout<<"\nCombined CrossEntropy Loss : "<<GlobalLoss;
        cout<<"\nUpdating weights"; 
       }
        MPI_Barrier(MPI_COMM_WORLD);

        MPI_Put(&LocalModel[0],size_model,Network,0,0,size_model,Network,win);
        MPI_Win_fence(0,win); 

          

       MPI_Barrier(MPI_COMM_WORLD);

       //Validate
       NN::Validate(MainModel,GlobalDataset,50);

        

    }

    else{
         

         //collect the dataset parts 
          MPI_Recv(LocalDataset,l_size,Data,0,1,MPI_COMM_WORLD,MPI_STATUS_IGNORE);

         //query the neural network
          MPI_Get(&LocalModel[0],size_model,Network,size-1,0,size_model,Network,win);
          MPI_Win_fence(0,win); 
          
          localLoss = NN::Forward(LocalModel,LocalDataset);
          NN::getGradients(localUpdates,LocalDataset,LocalModel);

      
    } 
     
   


   MPI_Win_free(&win);
   MPI_Finalize();
   
   return 0;

}
