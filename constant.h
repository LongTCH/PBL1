#pragma once
#define MAXC 1e308 //no direct path
#define MAX 100000 //max number of vertices
#define LINK "C:\\Users\\Hoang Long\\Desktop\\PBL\\matrix.txt"
#define ERR "Warning! Please enter valid data\n\n"
typedef struct node
{
    int vertex;
	double cost;
    struct node *next;
} Node;
typedef Node *pNode;

typedef struct
{
    int numVertices; 
    pNode *lists;
} Graph;
typedef Graph *pGraph;

