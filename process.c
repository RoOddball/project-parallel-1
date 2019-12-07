#include"ebolaHeader.h"

/*********************************************
 * populaceProcess: modifies the values in the targetArray argument by passing the values of
the array argument through the neighborFinder and the infectNeighbor functions and also by
 passing the targetArray 
values through the processTheSick function
 *********************************************/

void populaceProcess(int *array, int *targetArray, int * neighborsInd, int m,int localM, int myRank, int traditions,int quarantine){

  unsigned int i,k,index,mm;
  unsigned int firstElement = myRank*localM;
  unsigned int lastElement =(myRank+1)*localM;

  mm=m*m; 
  
  for(i=firstElement;i<lastElement;i++){

      printf("\n\n subject %d: %d ",i,targetArray[i]);

      for(k=0;k<8;k++){
	    
	index = neighborsInd[k+i*8];

	int infectedNeighbor = infectNeighbors(targetArray[index]);
	int element = array[i];

	if(element>0 && element<IMMUNE_TH && element>=INCUBATED_TH){

	  if(quarantine==0){
	    
	    printf("\n--processed neighbor%d: %d",index,targetArray[index]);
	    targetArray[index]=infectedNeighbor;
	    printf(" to %d ", targetArray[index]);

	  }else if(quarantine>0 && targetArray[i]<QUARANTINE_TH) {

	    printf("\n--processed neighbor%d: %d",index,targetArray[index]);
	    targetArray[index]=infectedNeighbor;
	    printf(" to %d", targetArray[index]);
	  } 
	}
      }
  }

  for(i=firstElement;i<lastElement;i++){

      printf("\n\n subject %d was:%d",i,targetArray[i]);
      targetArray[i] = processTheSick(targetArray[i],traditions);
      printf(" -- is: %d \n",targetArray[i]);
  }
}
