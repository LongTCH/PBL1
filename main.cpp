//#include <stdio.h>
#include <time.h>
#include <conio.h>
//#include <unistd.h>
#include "AllMethod.h"
#include "constant.h"
#include <Windows.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */
char LINK[100]="matrix.txt";
int trace[MAX];
int n,S,F,command,tp,sign=0;
double dA[MAX];
FILE *f;
pGraph graph; 
clock_t start,end;
double time_use;
void out(double cost);
void load();
void FindPath();
void FindLoc();
void intro();
void thanks();
char checkend();
void swap(int* a, int* b);
void selectionSort(int Map[], int n);
int main(int argc, char** argv) 
{
	intro();
LABEL:
	system("cls"); 
	SetConsoleTextAttribute(GetStdHandle( STD_OUTPUT_HANDLE ), 9);
	printf("Choose command in list\n");
	printf("1. Generate a new random matrix before loading\n");
	printf("2. Generate a new matrix from keyboard before loading\n");
	printf("3. Use the existed matrix\n");
	printf("4. End program\n");
	SetConsoleTextAttribute(GetStdHandle( STD_OUTPUT_HANDLE ), 9);
	printf("Command which you choose : ");
	fflush(stdin);
	do
	{
		command=getch();
	} while (command<'1' || command>'4');
	printf("%c\n",command);
	printf(LINE);
	SetConsoleTextAttribute(GetStdHandle( STD_OUTPUT_HANDLE ), 7);
	switch (command)
	{
		case '1': if(!initMat(f)) goto LABEL; load();  break;
		case '2': if(!EnterMatrix(f)) goto LABEL; load(); break;
		case '3': printf("Enter filename: "); gets(LINK); load(); break;
		case '4': if (checkend()=='y') thanks();
	}
	printf("Number of vertices: %d\n",n);
	do
	{
		SetConsoleTextAttribute(GetStdHandle( STD_OUTPUT_HANDLE ), 9);
		printf(LINE);
		printf("Choose next command in list\n");
    	printf("1. Find the shortest path between 2 vertices\n");
    	printf("2. Find all destinations of a vertex under a cost value\n");
		printf("3. End program\n");
		fflush(stdin);
		printf("Command which you choose : ");
		do
		{
			command=getch();
		} while (command<'1' || command>'3');
		printf("%c\n",command);
		printf(LINE);
		SetConsoleTextAttribute(GetStdHandle( STD_OUTPUT_HANDLE ), 7);
		switch (command)
		{
			case '1': FindPath(); break;
			case '2': FindLoc(); break;
			case '3': if (checkend()=='y') thanks();
		}
	} while(1);
	return 0;
}
void out(double cost)
{
	SetConsoleTextAttribute(GetStdHandle( STD_OUTPUT_HANDLE ), 6);
	if (cost==MAXC) printf("Path from %d to %d not found",S,F);
	else
	{
		printf("Distance from %d to %d is %.2lf\n",S,F,cost);
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
	graph = MatrixToList(f,&sign);
	end=clock();
    time_use = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Time used %lf\n\n", time_use);
	n=graph->numVertices;
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
    	Dijkstra(&dA[F],trace,graph,S,F);
    	out(dA[F]);
    	end=clock();
        time_use = (double)(end - start) / CLOCKS_PER_SEC;
        printf("\nTime used %lf\n", time_use);
	}
	else 
	{
		start=clock();
    	if (Ford_Bellman2(dA,trace,graph,S)==0) 
		{
			SetConsoleTextAttribute(GetStdHandle( STD_OUTPUT_HANDLE ), 6);
        	printf("Graph has negative circle. End program!\nPlease use the other graph and restart");
        	end=clock();
            time_use = (double)(end - start) / CLOCKS_PER_SEC;
            printf("\nTime used %lf\n", time_use);
			getch();
        	thanks();
        	
		}
		else
		{
        	out(dA[F]);
		}
    	end=clock();
        time_use = (double)(end - start) / CLOCKS_PER_SEC;
        printf("\nTime used %lf\n", time_use);
	}
}
void FindLoc()
{
	char temp;
	char str[101];
	double cost;
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
		printf("Enter cost value: "); 
		if (scanf("%100[-.0-9]s",str)==0) printf(ERR);
		else 
		{
			scanf("%c",&temp);
			if (temp!='\n' || checkinput1(str)==0) printf(ERR);
		   	else break;
		}
	} while (1);
	cost=atof(str);
	start=clock();
    	if (Ford_Bellman2(dA,trace,graph,S)==0) 
		{
			
			SetConsoleTextAttribute(GetStdHandle( STD_OUTPUT_HANDLE ), 6);
        	printf("Graph has negative circle. End program!\nPlease use another graph and restart");
        	end=clock();
            time_use = (double)(end - start) / CLOCKS_PER_SEC;
            printf("\nTime used %lf\n", time_use);
			getch();
        	thanks();
		}
		else
		{
			int Map[n+1];
			int countMap=0;
			for (int i=1; i<=n; i++)
			{
				if (i!=S && dA[i]<=cost) 
				{
					countMap++;
					Map[countMap]=i;
				}
			}
			printf("Number of destinations found: %d\n",countMap);
			selectionSort(Map,countMap);
			printf("|\tDestination\t|\t    Cost   \t|");
			for (int i=1; i<=countMap; i++)
			{
				printf("\n");
				printf("|\t%11d\t|\t%11.2lf\t|",Map[i],dA[Map[i]]);
			}
		}
    	end=clock();
        time_use = (double)(end - start) / CLOCKS_PER_SEC;
        printf("\nTime used %lf\n", time_use);
	}
void intro()
{
	int cc=1,icolor=1;
	f=fopen("intro.txt","r");
	char s[1000];
	while (!feof(f))
	{
		fgets(s,1000,f);
		if (cc%4==0) 
		{
			icolor++;
			SetConsoleTextAttribute(GetStdHandle( STD_OUTPUT_HANDLE ), icolor);
		}
		cc++;

		printf("%s",s);
	}
	fclose(f);
	Sleep(500);
	icolor=1;
	do
	{
    	SetConsoleTextAttribute(GetStdHandle( STD_OUTPUT_HANDLE ), icolor);
		printf("\t\t\tGETTING STARTED ."); Sleep(100);
		printf(" ."); Sleep(100);
		printf(" ."); Sleep(100);
		printf("\b\b\b\b\b\b");
		printf("      ");
	    printf("\r");
	    if (GetAsyncKeyState(VK_RETURN)) break;
	    icolor=1+(icolor++)%10;
	} while(1);
	
/*	for (int i=1; i<=99; i++) printf(" ");
	printf("%c\r",178);
	for (int i=0; i<=9; i++)
	{
		for (int j=1; j<=10; j++)
		{
			printf("%c",220);
			if (10*i+j==100) printf("100%%");
	    	Sleep(1.5*(i*4+j));
		}
		
	}
	Sleep(1000);
*/
getch();
}
void thanks()
{
	system("cls"); 
	int cc=1,icolor=1;
	f=fopen("thanks.txt","r");
	char s[1000];
	while (!feof(f))
	{
		fgets(s,1000,f);
		if (cc%4==0) 
		{
			icolor++;
			SetConsoleTextAttribute(GetStdHandle( STD_OUTPUT_HANDLE ), icolor);
		}
		cc++;
		printf("%s",s);
	}
	fclose(f);
	system("pause");
	exit(0);
}
char checkend()
{
	char check;
	printf("Sure to end ? Press 'y'(yes) or 'o'(no)");
	do 
	{
		check=getch();
	}while (check!='y'&&check!='o');
	printf("\n");
	return check;
}
void swap(int* a, int* b)
{
    int t = *a;
    *a = *b;
    *b = t;
}
 
void selectionSort(int Map[], int n)
{
    int i, j, min_idx;
    for (i = 1; i < n; i++)
	{
    	min_idx = i;
        for (j = i+1; j <= n; j++)  if (dA[Map[j]] < dA[Map[min_idx]])  min_idx = j;
     	swap(&Map[i], &Map[min_idx]);
	}
	
}


