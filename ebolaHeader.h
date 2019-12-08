#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <pthread.h>
#define IMMUNE_TH 1000
#define INCUBATED_TH 100
#define COUNTER_TO_STATE 100
#define INFECTED_TH 300
#define QUARANTINE_TH 400
#define DECEASED_TH 600
#define REMOVED_TH 900
float getRandomNumberFromRange(float, float);
void* childTurn(void*);
int threadCount;
int** currSubjects;
int m;
int turn;
int turnCount;
int traditions;
int quarantine;
int barrierCount1;
int barrierCount2;
int barrierTH;
int inputTurn;
pthread_mutex_t myLock1;
pthread_mutex_t myLock2;
pthread_mutex_t myLock3;
pthread_mutex_t myLock4;
