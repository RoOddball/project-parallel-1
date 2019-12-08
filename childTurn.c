#include "ebolaHeader.h"

void* childTurn(void *rank){
  printf("here i go");
  int localM = m*m/threadCount;
  long myRank = (long) rank;
  unsigned int i,k,index,mm;
  unsigned int firstElement = myRank*localM;
  unsigned int lastElement =(myRank+1)*localM;
  unsigned int neverInfected,survivors,incubated,infected,dead,removed,subject,sick;
  mm = m * m;
  neverInfected = 0;
  survivors = 0;
  incubated = 0;
  infected = 0;
  dead = 0;
  removed = 0;

  printf("\n\n\n\n i am thread %ld my m is %d, start %d finish %d",myRank,localM,localM*myRank,(myRank+1)*localM);

   printf("\n\n");

  pthread_mutex_lock(&myLock1);
  barrierCount1++;
  pthread_mutex_unlock(&myLock1);
  while(barrierCount1<threadCount);

  while(inputTurn>0){

    printf("\n\n\n\n i am thread %ld my m is %d, start %d finish %d \n i'm waiting",myRank,localM,localM*myRank,(myRank+1)*localM);
    

    printf("\n\n\n\n i am thread %ld my m is %d, start %d finish %d \n i'm in",myRank,localM,localM*myRank,(myRank+1)*localM);
    
    //populacProcess start
    for(i=firstElement;i<lastElement;i++){

      unsigned int mLong = m + m;
      unsigned int mShort = m/2;
      unsigned int row = (i-(m+i)%m)/m;
      unsigned int col = i%m;
      unsigned int leftCol = (m+col-1)%m;
      unsigned int rightCol = (col+1)%m;
      unsigned int upperRow = (m+row-1)%m;
      unsigned int lowerRow = (row+1)%m;
      unsigned int futureState = i+mm;
      int neighborsInd[8];

      neighborsInd[0] = leftCol+m*row;
      neighborsInd[1] = leftCol+m*upperRow;
      neighborsInd[2] = col+m*upperRow;
      neighborsInd[3] = rightCol+m*upperRow;
      neighborsInd[4] = rightCol+m*row;
      neighborsInd[5] = rightCol+m*lowerRow;
      neighborsInd[6] = col+m*lowerRow;
      neighborsInd[7] = leftCol+m*lowerRow;

       printf("\n\n subject %d: %d loc: row %d col %d neighbors:\n",i,currSubjects[futureState],row,col);

      for(k=0;k<8;k++){
	    
	index = neighborsInd[k]+mm;
	printf(" %d ",neighborsInd[k]);
	
	//infectNeighbor begin
	int neighbor = currSubjects[index];
	if(neighbor<IMMUNE_TH && neighbor>0 && neighbor<INCUBATED_TH){

	  float resistance;
	  
	  if(subject%100>15 && subject%INCUBATED_TH<50)

	    resistance = 67;
	  else{
    
	    resistance = 49;
	  }
	  if(getRandomNumberFromRange(0.0,resistance)<=1){

	    neighbor = neighbor+COUNTER_TO_STATE;
	  }
	}
	//infectNeighbor end
	
	int element =(int) currSubjects[i];

	if(element>0 && element<IMMUNE_TH && element>=INCUBATED_TH){

	  if(quarantine==0){
	    
	    printf("--processed neighbor%d:->%d %d",index-mm,index,currSubjects[index]);
	    currSubjects[index] = neighbor;
	    printf(" to %d \n", currSubjects[index]);

	  }else if(quarantine>0 && (int)currSubjects[futureState]<QUARANTINE_TH) {

	    printf("--processed neighbor%d: %d",index,currSubjects[index]);
	    currSubjects[index] = neighbor;
	    printf(" to %d \n", currSubjects[index]);
	  } 
	}
      }
  }

  for(i=firstElement;i<lastElement;i++){

    unsigned int futureState = i+mm;
    unsigned int subject = currSubjects[futureState];
    
    printf("\n\n subject %d-->%d was: %d",i,futureState,currSubjects[futureState]);

    //processTheSick begin
    if(subject<IMMUNE_TH && subject>=INCUBATED_TH)
      if(subject>=DECEASED_TH){

	printf("\n this subject is down");

	if(traditions>0){

	  if(subject<REMOVED_TH){

	    printf("\n traditions %d",traditions);
	    subject = subject+COUNTER_TO_STATE;
	  }else{

	    subject = 0;
	  }
        }else{

	  subject = 0;
	}
      }else{

	int stateEvolution = 1;

	if(subject<INFECTED_TH){
	  subject=subject+100;
	  stateEvolution--;
	}else{

	  if(getRandomNumberFromRange(0.0,10.0)<=9.0 && stateEvolution>0){

	    stateEvolution--;
	    printf("\n -- subject vizibly infected");
	    subject = subject + COUNTER_TO_STATE; 
	  }else{

	    subject=subject+IMMUNE_TH;
	    printf("\n !!subject outlasts desease");
	  }	  
	}
      }
    //processTheSick end

    currSubjects[futureState] = subject;
    printf(" -- is: %d \n",currSubjects[futureState]);
  }
  //populaceProcess end
  
  //populaceUpdate begin
  printf("\n\n");
 
 for(i=firstElement; i<lastElement; i++){
   
   unsigned int futureState = i+mm;

   printf("\n updating subject %d from: %d",i, currSubjects[i]);
   currSubjects[i]=currSubjects[futureState];
   printf(", to: %d",currSubjects[futureState]);        
 }
  //populaceUpdate end  
    printf("\n\n\nday: %d",turn);

    //sum begin
    for(i=firstElement;i<lastElement;i++){
      
      subject = (int)currSubjects[i];
    
    if(subject<INCUBATED_TH && subject>0){

      neverInfected++;
    }
    
    if(subject>=IMMUNE_TH){

      survivors++;
    }
    
    if(subject>=INCUBATED_TH && subject<INFECTED_TH){

      incubated++;
    }
    
    if(subject>=INFECTED_TH && subject<DECEASED_TH){

      infected++;
    }
    
      if(subject>=DECEASED_TH && subject<IMMUNE_TH){

	dead++;
    }
    
    if(subject==0){

	removed++;
    }	
  } 
  
  
  printf(" \n\n never infected: %d \n survivors: %d \n incubated: %d \n infected: %d \n dead: %d \n removed: %d \n\n\n",neverInfected,survivors,incubated,infected,dead,removed );

  sick = incubated + infected + dead;
    //sum end
    
    pthread_mutex_lock(&myLock2);
    inputTurn--;
    barrierCount2++;
    pthread_mutex_unlock(&myLock2);

    printf("i am thread %ld waiting for barrier 2 barrier count: %d where threashold is %d",myRank,barrierCount2,barrierTH);
    
    while(barrierCount2<barrierTH);

   
    pthread_mutex_lock(&myLock3);
    barrierCount2--;
    turnCount++;
    if(turnCount==barrierTH){
      
      turn++;
      turnCount = 0;
    }
    pthread_mutex_unlock(&myLock3);
    
  }

  pthread_mutex_lock(&myLock4);
  barrierCount2++;
  barrierTH--;
  printf("\ni %ld exited count is %d, threashold is %d",myRank,barrierCount2,barrierTH);
  pthread_mutex_unlock(&myLock4);

    return NULL;
}
