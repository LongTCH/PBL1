#include <stdio.h>
#include "constant.h"

static double d[MAX];//distance
static int Free[MAX];

void init_d(int trace[],  int n,  int S)
{
	for (int i=1; i<=n; i++) d[i]=MAXC;
	d[S]=0;
	for (int i=1; i<=n; i++) Free[i]=1;//all vertices is free
}

void Dijkstra(double *ShD, int trace[], pGraph graph, int S, int F)
{
	int n=graph->numVertices;
	int u,v;
	double min;
	pNode temp;
	init_d(trace,n,S);
	do
	{
		u=0; min=MAXC;
		for (v=1; v<=n; ++v)
		if (Free[v] && d[v]<min) 
		{
			min=d[v];
			u=v;
		}
		if (u==0 || u==F) break;
		Free[u]=0;//fix vertex
		temp=graph->lists[u]->next;
		while (temp!=NULL)
		{
			v=temp->vertex;
			if (Free[v] && (d[v]>d[u]+temp->cost))
			{
				d[v]=d[u]+temp->cost;
				trace[v]=u;
			}
			temp=temp->next;
		}
	}
	while (1);
	*ShD=d[F];
}


