#include "Layers.cpp"

int main()
{

    std::vector<Dense *> DNN;

    DNN.push_back(new Dense(3,5,"relu"));
    DNN.push_back(new Dense(5,5,"relu"));
    DNN.push_back(new Dense(5,2,"softmax"));

    std::cout<<"\nNeural Network Summary : "<<std::endl;

    for(auto l:DNN){

        l->layer_summary();
    } 

    return 0;



}