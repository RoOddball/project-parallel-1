#include"ebolaHeader.h"
/*********************************************
 * populationInitialize: this function populates the array passed as argument with values
and replaces the 0 from each value with a 1 if chances are
 *********************************************/

void populaceInitialize(int *array, int m,int localM,int myRank){

  unsigned int i,j,immunity,initialState,age;
  
  unsigned int firstElement = localM*myRank;
  unsigned int lastElement =(myRank+1)*localM;
    
  for(i=firstElement;i<lastElement;i++){
      if(getRandomNumberFromRange(0.0,10.0)<=1){

        immunity = IMMUNE_TH;
      }else{

        immunity = 0;
      }
      
      if(getRandomNumberFromRange(0.0,10.0)<=1 && immunity==0){

	initialState = INCUBATED_TH;
      }else{

	initialState = 0;
      }
      age =  round(getRandomNumberFromRange(1,99));
		   
      array[i] = immunity + initialState +age;    
      printf("\n-- subject: %d  --intialized -|- immunity is: %d -|- state is: %d -|- age is: %d --> %d ", i,immunity,initialState,age,array[i]);
    
  }
}
