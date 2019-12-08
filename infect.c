#include"ebolaHeader.h"
/*********************************************
 * infectNeighbors: this function takes a value, checks if the last three digits are larger
 then 200 in which case it is ignored, else if its less than 100 it will be at a
random chance added to 100 or ignored
 *********************************************/

int infectNeighbors(int* neighbor){
  
  
  if((int)neighbor<IMMUNE_TH && neighbor>0 && (int)neighbor<INCUBATED_TH){

    if(getRandomNumberFromRange(0.0,resistance((int)neighbor))<=1){

      neighbor = neighbor+COUNTER_TO_STATE;
    }
  }
  return (int)neighbor;
}
