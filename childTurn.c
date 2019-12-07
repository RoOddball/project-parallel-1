#include "ebolaHeader.h"

void* childTurn(void *rank){

  int i,sick;
  int localM = m*m/threadCount;
  long myRank = (long) rank;

  printf("\n\n\n\n i am thread %d my m is %d, start %d finish %d",myRank,localM,localM*myRank,(myRank+1)*localM);

  populaceUpdateChild(currSubjects,futSubjects,localM,myRank);
  sick = sumUp(currSubjects,localM,myRank);

  pthread_mutex_lock(&myLock1);
  barrierCount1++;
  pthread_mutex_unlock(&myLock1);
  while(barrierCount1<threadCount);

  while(inputTurn>0){

    if(myRank==0)
      turn++;

    printf("\n\n\n\n i am thread %ld my m is %d, start %d finish %d \n i'm waiting",myRank,localM,localM*myRank,(myRank+1)*localM);
    

    printf("\n\n\n\n i am thread %ld my m is %d, start %d finish %d \n i'm in",myRank,localM,localM*myRank,(myRank+1)*localM);
    
    populaceProcess(currSubjects,futSubjects,neighborsInd,m,localM,myRank,traditions,quarantine);
    populaceUpdateChild(futSubjects,currSubjects,localM,myRank);
    printf("\n\n\nday: %d",turn);
    sick = sumUp(currSubjects,localM,myRank);


    pthread_mutex_lock(&myLock2);
    inputTurn--;
    barrierCount2++;
    pthread_mutex_unlock(&myLock2);

    printf("i am thread %ld waiting for barrier 2 barrier count: %d where threashold is %d",myRank,barrierCount2,barrierTH);
    
    while(barrierCount2<barrierTH);

   
    pthread_mutex_lock(&myLock3);
    barrierCount2--;
    pthread_mutex_unlock(&myLock3);
    
  }

  pthread_mutex_lock(&myLock4);
  barrierCount2++;
  barrierTH--;
  printf("\ni exited count is %d, threashold is %d",barrierCount2,barrierTH);
  pthread_mutex_unlock(&myLock4);

    return NULL;
}
