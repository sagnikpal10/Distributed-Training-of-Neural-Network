/*************** Utility function to create a profile matrix from given protein and its arbitary alignments **************/
/* @author : Abhishek Jha */

#include "../Matrix/Matrix.cpp"
#include<iostream>
#include<string>
#include<map>

#pragma once

/*
   There are total 20 amino acids and 1C and 1N terminal so the profile matrix has a shape of 22 * window_size.
   Therefor the total size of input generated from a given protein sequence is 20*window_size*number_of_windows
*/

#define NUM_PROTEINS 22

/* create a map of amino acid residue to its respective index */
typedef  std::map<char,double>  amino_index_map;



//Initialize the amino acid map

char amino_acids[NUM_PROTEINS] = {'A','B','C','D','E','F','G','H','I','G','J','K','L','M','N','O','P','Q','R','S'};

void initialize_map(amino_index_map & acid_map){

    for(int i=0;i<NUM_PROTEINS;i++)
        acid_map.insert(std::pair<char,int>(amino_acids[i],0.0));
    
}

void reset_map(amino_index_map & acid_map){
     
     for(int i=0;i<NUM_PROTEINS;i++)
        acid_map[amino_acids[i]]=0.0;

}


//Function to return the profile matrix in windows for a given protein sequence

std::vector<double> get_profile(std::vector<std::vector<char>> & sequences,int window_size){


       /* get the number of sequences for the given data */
       int num_alignments = sequences.size();

       std::cout<<"\n\nNumber of alignments : "<<num_alignments<<std::endl;

       /* get the length of protein sequences */
       int length_sequences = sequences[0].size();

       std::cout<<"\n\nLength of each sequence : "<<length_sequences<<std::endl;


       std::vector<double> profile;
       
       std::vector<double> window_map;


       amino_index_map residue_count;
       initialize_map(residue_count);

       /* Visualize the initilaize map */

       std::cout<<"\nInitial map";
       amino_index_map::iterator itr;  
       for(itr=residue_count.begin();itr!=residue_count.end();itr++){

           std::cout<<itr->first<<" : "<<itr->second<<std::endl;
       } 


       std::vector<double> profile_vector;

       std::vector<std::vector<double>> window_amino_vectors;



       for(int i=0;i<length_sequences;i++){


           std::vector<double> row_vec;      
           
           
        
        /********************************  INITALIZE THE WINDOW  ******************************************************/
          
           while(i<window_size){

                std::vector<double> row_vec;                                 
                /* initialize a row amino_acid_map to store the counts of residues */

                reset_map(residue_count);
                   
                /* incerement the count for the protein by a unit */
                /* incrementing by a unit means +(1/num_alignments) */

                   residue_count[sequences[0][i]]+= (double)1/num_alignments;

                   for(int j=1;j<num_alignments;j++){

                       residue_count[sequences[j][i]]+=(double)1/num_alignments;    
                   }
                   
                   /* Visualize the map for ith row */
                   std::cout<<"\n\nMap for "<<i+1<<"th row"<<std::endl;
                   amino_index_map::iterator itr1;  
                   for(itr1=residue_count.begin();itr1!=residue_count.end();itr1++){
                      std::cout<<itr1->first<<" : "<<itr1->second<<std::endl;
                   } 

                   /* create the row vector of counts */
                  
                   for(int a=0;a<NUM_PROTEINS;a++){

                       row_vec.push_back(residue_count[amino_acids[a]]);
                   }

                   //Visualize the row vector for ith row 
                   std::cout<<"\nRow vec for "<<i+1<<"th row"<<std::endl;
                   for(int k=0;k<row_vec.size();k++)
                       std::cout<<row_vec[k]<<" ";

                   window_amino_vectors.push_back(row_vec);

                   i++;

                   if(i==window_size){

                      /* append the flattened window vector to the profile vector */

                      for(int l=0;l<window_size;l++){

                          for(int m=0;m<NUM_PROTEINS;m++){

                              profile_vector.push_back(window_amino_vectors[l][m]);

                          }
                      }

                      //Visualize the window vector
                      std::cout<<"\n\n\nWindow vectors"<<std::endl;
                      for(int l=0;l<window_size;l++){

                          for(int m=0;m<NUM_PROTEINS;m++){

                              std::cout<<window_amino_vectors[l][m]<<" ";

                          }
                          std::cout<<"\n";
                      }
                    reset_map(residue_count);
                  }
               }

    /************************  ADD NEW VECTOR TO THE WINDOW AND REMOVE THE FIRST ROW *********************************************/        

               residue_count[sequences[0][i]]+= (double)1/num_alignments;

                   for(int j=1;j<num_alignments;j++){

                       residue_count[sequences[j][i]]+=(double)1/num_alignments;    
                   }
                   

                   /* create the row vector of counts */
                   
                   for(int a=0;a<NUM_PROTEINS;a++){

                       row_vec.push_back(residue_count[amino_acids[a]]);
                   }

                   window_amino_vectors.push_back(row_vec);

                   

                   window_amino_vectors.erase(window_amino_vectors.begin());
                   for(int i=0;i<window_size;i++){

                          for(int j=0;j<NUM_PROTEINS;j++){

                              profile_vector.push_back(window_amino_vectors[i][j]);

                          }
                      }

                   //Visualize the window vector
                      std::cout<<"\n\n\nWindow vectors"<<std::endl;
                      for(int l=0;l<window_size;l++){

                          for(int m=0;m<NUM_PROTEINS;m++){

                              std::cout<<window_amino_vectors[l][m]<<" ";

                          }
                          std::cout<<"\n";
                      }

            reset_map(residue_count);              
               

           }

           return profile_vector;

    }
/*
int main(){

    std::vector<std::vector<char>> sequences;

    

    char sequence[4][10] = {{ 'A','B','C','E','F','J','K','L','M','N'},
                            { 'A','C','C','E','F','J','L','L','M','N'},
                            { 'A','C','D','F','F','J','K','L','N','N'},
                            { 'A','B','C','G','G','J','I','L','M','N'}} ;
                                

    for(int i=0;i<4;i++){

        std::vector<char> align;
        for(int j=0;j<10;j++)
           align.push_back(sequence[i][j]);

        sequences.push_back(align);    

    } 

    std::vector<double> profile = get_profile(sequences,5);
    

    std::cout<<profile.size()<<"\n\n";
    for(int i=0;i<profile.size();i++)
       std::cout<<profile[i]<<" ";

   

    return 0;   


}        

*/    


