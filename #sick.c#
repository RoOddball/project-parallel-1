#include "ebolaHeader.h"
/*********************************************
 * processTheSik: this function takes an integer argument, checks if its last three digits
 are equal or larger than 100, then if its larger than 200 in which case it will be ignored,
else at a random chance it will either added to 100 or to 900 or ignored
 *********************************************/

int processTheSick(int subject,int traditions){

  if(subject<IMMUNE_TH && subject>=INCUBATED_TH){
    
    //  srand((unsigned int)time(NULL));
    
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
  }
  
  return subject;
}
