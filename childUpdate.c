#include "ebolaHeader.h"

void populaceUpdateChild(int** array, int** targetArray, int localM, int myRank){

  
  unsigned int i,start,limit;
  
  start = myRank*localM;
  limit = (myRank+1)*localM ;
  
 printf("\n\n");
 
 for(i=start; i<limit; i++){
   
   printf("\n updating subject %d from: %d",i, targetArray[i]);
   targetArray[i]=array[i];
   printf(", to: %d",array[i]);
        
 }
}
