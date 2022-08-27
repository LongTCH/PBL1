#include <stdio.h>
#include "constant.h"

/*
void init_d(double d[], int trace[],  int n,  pGraph graph,  int S)
{
	pNode temp=graph->lists[S]->next;
	for (int i=1; i<=n; i++) d[i]=MAXC;
	d[S]=0;
	while (temp!=NULL)
	{
		d[temp->vertex]=temp->cost;//distance firstly is cost
		temp=temp->next;	
	}
	for (int i=1; i<=n; i++) 
	{
		trace[i]=S;//initial path to other vertices is from starting vertex
	}
}

int Ford_Bellman(double d[], int trace[], pGraph graph, int S) 
{
	int n=graph->numVertices;
	int CountLoop = 0;
	int i, j, Stop;
	pNode temp;
	init_d(d,trace,n,graph,S);
	do {
		Stop = 1;
		for (i = 1; i <= n; i++) 
		{
			temp=graph->lists[i]->next;
			while (temp!=NULL)
			{
				j=temp->vertex;
				if (d[j] > (d[i] + temp->cost)) 
				{
					d[j] = d[i] + temp->cost;
					trace[j] = i;
					Stop = 0;
				}
				temp=temp->next;
			}
		}
		CountLoop++;
	} while (!Stop && CountLoop < n - 2);
//check for negative circle
	for (i = 1; i <= n; i++) 
	{
		temp=graph->lists[i]->next;
		while (temp!=NULL) 
		{
			j=temp->vertex;
			if (d[j] > (d[i] + temp->cost)) return 0;
			temp=temp->next;
	    }
	}
	return 1;
}
*/

int Ford_Bellman2(double d[], int trace[], pGraph graph, int S)
{
	int n=graph->numVertices;
	int u,v,front=0,rear=0,count=0;
	int Queue[n];
	int InQueue[n+1]={0};//check if u exists in Queue
	int check[n+1]={0};//check how many times a path is upgraded
	pNode temp;
	for (int i=1; i<=n; i++) d[i]=MAXC;
	d[S]=0;
	Queue[0]=S;//Firstly add S to Queue
	InQueue[S]=1;
	do
	{
		u=Queue[front];//DeQueue
		InQueue[u]=0;
		front=(front+1)%n;
		temp=graph->lists[u]->next;
		while (temp!=NULL)
		{
			v=temp->vertex;
			if (d[v] > (d[u] + temp->cost)) 
			{
				d[v] = d[u] + temp->cost;
				trace[v] = u;
				if (check[v]==n) return 0;//check for negative circle
				else ++check[v];
				if (InQueue[v]==0) 
				{
					//EnQueue
					rear=(rear+1)%n;
					Queue[rear]=v;
					InQueue[v]=1;
				}
			}
			temp=temp->next;
		}
	} while (front != (rear+1)%n);
	return 1;
}
