#ifndef allmethod
#define allmethod
#include <stdio.h>
#include "constant.h"

void Dijkstra(double *ShD, int trace[], pGraph graph, int S, int F);

//int Ford_Bellman(double d[], int trace[], pGraph graph, int S);

int Ford_Bellman2(double d[], int trace[], pGraph graph, int S);

int initMat(FILE *f);

int EnterMatrix(FILE *f);

pGraph MatrixToList(FILE *f, int *sign);

int checkinput1(char *s);
#endif


