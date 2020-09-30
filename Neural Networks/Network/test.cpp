#include "Train.cpp"
//#include "Network.cpp"

int main()
{

   NeuralNetwork NN;

   NN.add(new Layer(3,5,"relu",true,false));
   NN.add(new Layer(5,4,"relu",false,false));
   NN.add(new Layer(4,3,"sigmoid",false,true));
   //NN.add(new Layer(3,3,"sigmoid",false,true));

   Matrix test;
   test.init(3,1);
   test = test.applyFunction(random_init);

   //print the matrices of Neural network
   
   
   std::cout<<"\n\nThe initial weights are : "<<std::endl;
   for(auto l:NN.Layers){
       l->W.print();
       std::cout<<"\n\n";
   }
   

  // for(int i=0;i<10;i++){

      //Matrix test(3,1);
      //test = test.applyFunction(random_init);
      //test.print();
      std::cout<<"\n\n\n Test Back Propagation\n\n\n";
      Matrix out = NN.feed_forward(test);
      out.print();
      BackPropagate(NN,out,test,0.1);
   
  // }
   

   
   
   /*
   std::cout<<"\n\nThe weights after update are : "<<std::endl;
   for(auto l:NN.Layers){
       l->W->print();
       std::cout<<"\n\n";
   }
   */

   return 0;

}