#include"ebolaHeader.h" 
/*********************************************
 * neighborFinder: this function does....
 *********************************************/

void neighborFinder(int *neighborsInd, int index, int m){

  unsigned int row = (index-(m+index)%m)/m;
  unsigned int col = index%m;
  unsigned int leftCol = (m+col-1)%m;
  unsigned int rightCol = (col+1)%m;
  unsigned int lowerRow = (m+row-1)%m;
  unsigned int upperRow = (row+1)%m;
  unsigned int neighborCol = index*8;
  
  neighborsInd[0+neighborCol] = leftCol+m*row;
  neighborsInd[1+neighborCol] = leftCol+m*upperRow;
  neighborsInd[2+neighborCol] = col+m*upperRow;
  neighborsInd[3+neighborCol] = rightCol+m*upperRow;
  neighborsInd[4+neighborCol] = rightCol+m*row;
  neighborsInd[5+neighborCol] = rightCol+m*lowerRow;
  neighborsInd[6+neighborCol] = col+m*lowerRow;
  neighborsInd[7+neighborCol] = leftCol+m*lowerRow;
  
}
