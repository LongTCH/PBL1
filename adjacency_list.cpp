#include <stdio.h>
#include <stdlib.h>
#include "constant.h"


pNode CreateNode(int d, double val)
{
    pNode newNode;
	newNode = (pNode)malloc(sizeof(Node));
    newNode->vertex = d;
	newNode->cost = val;
    newNode->next = NULL;
    return newNode;
}

pGraph CreateGraph(int vertices)
{

    pGraph newGraph;
	newGraph = (pGraph)malloc(sizeof(Graph));

    newGraph->numVertices = vertices;

    newGraph->lists = (pNode *)malloc((vertices+1) * sizeof(pNode));

    int i;
    pNode temp;
    for (i = 1; i <= vertices; i++)
    {
        temp = CreateNode(i, 0); 
        newGraph->lists[i] = temp;
    }
 
    return newGraph;
}
void AddEdge(pGraph graph, int s, int d, double val)
{
    
    pNode newNode = CreateNode(d, val);
  
    newNode->next = graph->lists[s]->next;
   
    graph->lists[s]->next = newNode;
 
}

pGraph MatrixToList(FILE *f, int *sign)
{
	int n,tp;
	f=fopen(LINK,"r");
	if (fscanf(f,"%d",&n)==EOF || n<=0) 
	{
		printf("Data file is not valid. End program!");
		exit(0);
	}
	pGraph graph = CreateGraph(n);
	double val;
	pNode temp;
    for (int i = 1; i <= graph->numVertices; i++)
    {
      	for (int j=1;j<=graph->numVertices;j++)
      	{
      		if (fscanf(f,"%lf", &val)==0)
      		{
				printf("Data file is not valid. End program!");
				exit(0);
			}
			if(val<0) *sign=1;
			if (val<MAXC) AddEdge(graph,i,j,val);
		}
	}
	char last[256];
	fscanf(f,"%[ ,\n]s",last);
	if (!feof(f)) 
	{
		printf("Data file is not valid. End program!");
		exit(0);
	} 
    fclose(f);
    return graph;
}
//double cache[vertice];
//void InitCache(int n)
//{
//	for (int i=1; i<=n; i++) cache[i]=MAXC;
//}
//void Endpr(pGraph graph, FILE *f)
//{
//	pNode temp;
//	f=fopen(LINK,"w");
//	fprintf(f,"%d\n",graph->numVertices);
//	for (int i=1; i<=graph->numVertices; i++)
//	{
//		InitCache(graph->numVertices);
//		temp=graph->lists[i]->next;
//		while (temp!=NULL)
//		{
//			cache[temp->vertex]=temp->cost;
//			temp=temp->next;
//		}
//		for (int j=1; j<=graph->numVertices; j++) 
//		if (cache[j]==MAXC) fprintf(f,"%.0e ",MAXC);
//		else fprintf(f,"%.2lf ",cache[j]);
//		fprintf(f,"\n");
//	}
//	fclose(f);
//}
