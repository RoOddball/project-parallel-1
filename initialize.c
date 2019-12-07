#include"ebolaHeader.h"
/*********************************************
 * populationInitialize: this function populates the array passed as argument with values
and replaces the 0 from each value with a 1 if chances are
 *********************************************/

void populaceInitialize(int *array, int m){

  unsigned int i,mm,immunity,initialState,age;
  mm=m*m;
  
  
  for(i=0;i<mm;i++){
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
      printf("\n-- subject: %d  --intialized -|- immunity is: %d -|- state is: %d -|- age is: %d --> %d ",i,immunity,initialState,age,array[i]);
    
  }
}

