#include"ebolaHeader.h"
/*********************************************
 * getRandomNumberFromRange: returns random float from the range passed as arguments
 *********************************************/

float getRandomNumberFromRange(float x, float y){

  int result =  x + (y-x)*((float)rand()) / ((float)RAND_MAX);

  return result;		    
}
