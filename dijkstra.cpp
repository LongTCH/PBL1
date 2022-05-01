#include <stdio.h>
#include "constant.h"


int nHeap;
double d[MAX];//distance
int heap[MAX];//store name of vertex put in node
int Free[MAX];
double cacheArr[MAX];//store cost u->v while processing

void swapNode(int a, int b);//swap two vertices in HEAP
void init_d(int trace[],  int n,  pGraph graph,  int S);//generate first configures
void buildHeap();
void heapify(int i);
void heapSort();//remove root
void initCache(int n);


void Dijkstra(double *ShD, int trace[], pGraph graph, int S, int F)
{
	int n=graph->numVertices;
    nHeap=n;
	int u,v;
	init_d(trace,n,graph,S);
	buildHeap();//frist construction of HEAP
	do
	{
//		printf("%lf\n",d[F]);
		u=heap[1];//get root of min HEAP
		if (u==F) break;
		Free[u]=0;//fix vertex
		pNode temp=graph->lists[u]->next;
    	initCache(graph->numVertices);
		while (temp!=NULL)
    	{
    		cacheArr[temp->vertex]=temp->cost;
    		temp=temp->next;
    	}
		for (v=1; v<=n; v++)
		{
			if (Free[v] && (d[v]>d[u]+cacheArr[v]))
			{
				d[v]=d[u]+cacheArr[v];
				trace[v]=u;
			}
		}
		heapSort();//after fixing a vertex, remove it from HEAP
	}
	while (nHeap!=0);
	*ShD=d[F];
}
void init_d(int trace[],  int n,  pGraph graph,  int S)
{
	pNode temp=graph->lists[S]->next;
	for (int i=1; i<=graph->numVertices; i++) d[i]=MAXC;
	while (temp!=NULL)
	{
		d[temp->vertex]=temp->cost;//distance firstly is cost
		temp=temp->next;
		
	}
	for (int i=1; i<=n; i++) 
	{
		heap[i]=i;//transmit vertices into HEAP before construction
		trace[i]=S;//initial path to other vertices is from starting vertex
		Free[i]=1;//all vertices is free
	}
}

void swapNode(int a, int b)
{
	int temp=heap[a];
	heap[a]=heap[b];
	heap[b]=temp;
}
void heapify(int i)
{
    int parent = i;
    int l = 2 * i;
    int r = 2 * i + 1;
    if (l <= nHeap && d[heap[l]] < d[heap[parent]])
        parent = l;
    if (r <= nHeap && d[heap[r]] < d[heap[parent]])
        parent = r;
    if (parent!=i) 
    {
    	swapNode(i,parent);
		heapify(parent);
	}
}
 
void buildHeap()
{
    int startIdx = nHeap / 2;
    for (int i = startIdx; i > 0; i--) {
        heapify(i);
    }
}

void heapSort()
{
    swapNode(1, nHeap);
    nHeap--;
    buildHeap();
}
void initCache(int n)
{
	for (int i=1; i<=n; i++) cacheArr[i]=MAXC;
}

