#pragma once
#include <stdio.h>
#include "constant.h"

void Dijkstra(double *ShD, int trace[], pGraph graph, int S, int F);

void initMat(FILE *f);

void EnterMatrix(FILE *f);

pGraph MatrixToList(FILE *f, int *sign);
