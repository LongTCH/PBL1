#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <conio.h>
#include "AllMethod.h"
#include "constant.h"

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int trace[MAX];
int n,S,F,command,tp,sign=0,stop=0,endpr=0,rewrite=0;
double ShD;
FILE *f;
pGraph graph;
clock_t start,end;
double time_use;
void out();
void load();
void FindPath();
void outMat();
void stoppr();
int main(int argc, char** argv) 
{
	system("color F0");
	printf("Choose command in list\n");
	printf("1. Generate a new random matrix before loading\n");
	printf("2. Generate a new matrix from keyboard before loading\n");
	printf("3. Load the exist matrix\n");
	printf("4. End program\n");
	do
	{
		printf("Command which you choose : ");
		fflush(stdin);
		do
		{
			command=getch();
		} while (command<'1' || command>'4');
		printf("%c\n",command);
		switch (command)
		{
			case '1': initMat(f); load(); stop=1; break;
			case '2': EnterMatrix(f); load(); stop=1; break;
			case '3': load(); stop=1; break;
			case '4': stop=1; endpr=1; break;
			default: printf(ERR);
		}
	} while(stop==0);
	if (endpr==1) 
	{
		printf("Good bye");
		return 0;
	}
	stop=0;

	do
	{
		printf("Choose next command in list\n");
    	printf("1. Find the shortest path between 2 vertices\n");
    	printf("2. Find all locations with shortest distance smaller than a radius\n");
		printf("3. End program\n");
		fflush(stdin);
		printf("Command which you choose : ");
		do
		{
			command=getch();
		} while (command<'1' || command>'3');
		printf("%c\n",command);
		switch (command)
		{
			case '1': FindPath(); break;
			case '2': break;
			case '3': stop=1; break;
			default: printf(ERR);
		}
	} while(stop==0);
    printf("Good bye");
	getch();
	return 0;
}
void out()
{
	if (ShD==MAXC) printf("Path from %d to %d not found",S,F);
	else
	{
		printf("Distance from %d to %d is %.2lf\n",S,F,ShD);
		while (F!=S)
		{
			printf("%d <- ",F);
			F=trace[F];
		}
		printf("%d",S);
	}
}
void load()
{
	printf("Loading graph...\n");
	start=clock();
	graph = MatrixToList(f,&stop);
	end=clock();
    time_use = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Time used %lf\n\n", time_use);
	n=graph->numVertices;
	printf("Number of vertices: %d\n",n);
}
void FindPath()
{
	char temp;
	do
       	{
       		fflush(stdin);
       		printf("Enter starting vertex "); 
       		if (scanf("%d%c",&S,&temp)!=2 || temp!='\n' || S<1 || S>n) printf(ERR);
			else break;
    	} while (1);
    do
       	{
       		fflush(stdin);
       		printf("Enter finishing vertex ");
       		if (scanf("%d%c",&F,&temp)!=2 || temp!='\n' || F<1 || F>n) printf(ERR);
       		else break;
        } while (1);
	if (sign==0) 
	{
		start=clock();
    	Dijkstra(&ShD,trace,graph,S,F);
    	out();
    	end=clock();
        time_use = (double)(end - start) / CLOCKS_PER_SEC;
        printf("\nTime used %lf\n", time_use);
	}
}
