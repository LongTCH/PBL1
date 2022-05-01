#include <stdio.h>
#include <conio.h>
#include <time.h>
#include <stdlib.h>
#include "constant.h"
//#include <float.h>
void initMat(FILE *f)
{
	char check;
	printf("Are you sure to generate a new matrix?\nThe exist one will be deleted!\nEnter anything begin with 'y'(if yes) or 'o'(if no)\n");
	do
	{
		fflush(stdin);
		check=getch();
	} while (check != 'y'  && check != 'o');
	if (check=='o') return;
	f=fopen(LINK,"w");
	srand(time(NULL));
	int n,tp;
	char temp;
	do
	{
		fflush(stdin);
		printf("Enter number of vertices: "); 
		if (scanf("%d%c",&n,&temp)!=2 || temp!= '\n' || n<=0) printf(ERR);
		else break;
	} while (1);
	
	fprintf(f,"%d\n",n);
	printf("Gererating Matrix...\n");
	clock_t start,end;
    start=clock();
	for (int i=1; i<=n; i++)
	{
		for (int j=1; j<=n; j++)
    	{
    		if (i==j) fprintf(f,"%d ",0);
     		else 
    		{
    			tp=101+rand()%1001;
        		if (tp>500) fprintf(f,"%.0e ",MAXC);
    			else fprintf(f,"%d ",tp);
    		}
    	}
    	fprintf(f,"\n");
	}
	end=clock();
    double time_use = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Time used %lf\n\n", time_use);
	fclose(f);
}
