#include"ebolaHeader.h"
/*********************************************
 * populaceUpdate: copies array with address passed as argument 1 into array passed as 
argument 2 of size passed as argument 3
 *********************************************/

void populaceUpdate(int **array,int **targetArray,int m){

 unsigned int i;

 printf("\n\n");
 
 for(i=0; i<m*m; i++){

   
      printf("\n updating subject %d from: %d",i, targetArray[i]);
      targetArray[i]=array[i];
      printf(", to: %d",array[i]);
     
    
 }
}
