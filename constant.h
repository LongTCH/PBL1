#ifndef constant
#define constant
#define MAXC 1e108 //no direct path
#define MAX 10000 //max number of vertices
//#define LINK "matrix.txt"
#define ERR "Warning! Please enter valid data\n\n"
#define LINE "*****************************0o0***************************\n"
extern char LINK[100];
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
#endif


