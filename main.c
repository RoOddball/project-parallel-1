
#include "ebolaHeader.h"

int main(){
   
  unsigned int i,mm,immunity,initialState,age;

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
  mm = m*m;
  barrierCount1 = 0;
  barrierCount2 = 0;
  turnCount = 0;
  barrierTH = threadCount;
  inputTurn = inputTurn*threadCount;
  long thread;
  pthread_t *thread_handles;

  currSubjects = (int **)malloc(m*sizeof(int *));
  for(i=0;i<m;i++)
    currSubjects[i] = (int *)malloc(m*2*sizeof(int));
  
  for(i=0;i<mm;i++){
    
    unsigned int futureState = i+mm;
    
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
		   
      currSubjects[i] = (int*)(immunity + initialState +age);
      currSubjects[futureState] = (int*)(immunity + initialState +age);
      printf("\n-- subject: %d  --intialized -|- immunity is: %d -|- state is: %d -|- age is: %d --> %d future state --> %d",i,immunity,initialState,age,currSubjects[i],currSubjects[futureState]);
    
  }
  
  thread_handles = (pthread_t*)malloc(threadCount*sizeof(pthread_t));
  
  for(thread=0; thread<threadCount; thread++)
    pthread_create(&thread_handles[thread],NULL,childTurn,(void*)thread);

  for(thread=0; thread<threadCount; thread++)
    pthread_join(thread_handles[thread],NULL);

  pthread_mutex_destroy(&myLock1);
  pthread_mutex_destroy(&myLock2);
  pthread_mutex_destroy(&myLock3);
  pthread_mutex_destroy(&myLock4);
  free(thread_handles);
  
  for(i=0;i<m;i++)
    free(currSubjects[i]); 

  free(currSubjects);

  printf("\n -- free cell :%d",&currSubjects[0][0]);
  printf("\n -- free pointer :%d",&currSubjects);

   return 0;
}
