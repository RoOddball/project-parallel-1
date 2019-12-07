
#include "ebolaHeader.h"

int main(){
   
  int sick,i;
  float x,y;

  printf( "\n Please input the size of the matrix \n");
  scanf("%d",&m);
  printf("\n size is: %d \n",m);

  printf( "\n Please input the turn you wish to run \n");
  scanf("%d",&inputTurn);
  printf("\n turns : %d \n",m);

  printf("Please input number of threads:");
  scanf("%d",&threadCount);
  if(threadCount>8)
    threadCount = 1;
  printf("\n threads: %d\n",threadCount);

  printf( "\n Please select option... Do you wish to consider the tradition of mourning the dead for 3 turns?(1/0) \n");
  scanf("%d",&traditions);
  printf("\n traditions is: %d \n",traditions);

  printf( "\n Please select option... Do you wish to consider the quarantine feature?(1/0)\n");
  scanf("%d",&quarantine);
  printf("\n quarantine is: %d \n",quarantine);

  turn =0;
  int mm = m*m;
  mainTurnSwitch = 1;
  barrierCount1 = 0;
  barrierCount2 = 0;
  barrierTH = threadCount;
  inputTurn = inputTurn*threadCount;
  long thread;
  pthread_t *thread_handles;

  thread_handles = malloc(threadCount*sizeof(pthread_t));
  
  neighborsInd = (int **)malloc(mm*sizeof(int *));
  for(i=0;i<mm;i++)
    neighborsInd[i] = (int *)malloc(8*sizeof(int));
  
  futSubjects = (int **)malloc(m*sizeof(int *));
  for(i=0;i<m;i++)
    futSubjects[i] = (int *)malloc(m*sizeof(int));

  currSubjects = (int **)malloc(m*sizeof(int *));
  for(i=0;i<m;i++)
    currSubjects[i] = (int *)malloc(m*sizeof(int));

  for(i=0;i<mm;i++)
    neighborFinder(neighborsInd,i,m);

  for(i=0;i<mm;i++){

    printf("\n neighbors of %d are ",i);
    for(int j=0;j<8;j++)
      printf(" %d",neighborsInd[j+i*8]);
	}

  populaceInitialize(currSubjects,m);
  
  for(thread=0; thread<threadCount; thread++)
    pthread_create(&thread_handles[thread],NULL,childTurn,(void*)thread);

  for(thread=0; thread<threadCount; thread++)
    pthread_join(thread_handles[thread],NULL);

  pthread_mutex_destroy(&myLock1);
  pthread_mutex_destroy(&myLock2);
  pthread_mutex_destroy(&myLock3);
  pthread_mutex_destroy(&myLock4);
  free(thread_handles);
  for(i=0;i<m;i++){

    free(currSubjects[i]);
    free(futSubjects[i]);
    
  }

  free(currSubjects);
  free(futSubjects);
  
  for(i=0;i<mm;i++)
    free(neighborsInd[i]);

  free(neighborsInd);
    
  printf("\n -- free cell :%d",&currSubjects[0][0]);
  printf("\n -- free pointer :%d",&currSubjects);

    printf("\n -- free cell :%d",&futSubjects[0][1]);
   printf("\n -- free pointer :%d",&futSubjects);

   return 0;
}
