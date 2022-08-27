#include <stdio.h>
#include <conio.h>
#include <time.h>
#include <stdlib.h>
#include "constant.h"
//#include <float.h>
int initMat(FILE *f)
{
	char check;
	printf("Are you sure to generate a new matrix?\nThe existed one will be deleted!\nPress 'y'(if yes) or 'o'(if no)\n");
	do
	{
		fflush(stdin);
		check=getch();
	} while (check != 'y'  && check != 'o');
	if (check=='o') return 0;
	f=fopen(LINK,"w");
	srand(time(NULL));
	int n,tp;
	char str[101];
	char temp;
	do
	{
		do
		{
			fflush(stdin);
	    	printf("Enter number of vertices: (1<n<10000) "); 
	    	if (scanf("%4[0-9]s",str)==0) printf(ERR);
	    	else 
	    	{
	    		scanf("%c",&temp);
	    		if (temp!='\n') printf(ERR); else break;
	    	}
    	} while (1);
    	n=atoi(str);
    	if (n<2) printf(ERR); else break;
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
    			tp=1+rand()%10000;
				if (tp>5000) fprintf(f,"%.0e ",MAXC);
    			else fprintf(f,"%d ",tp);
    		}
    	}
    	fprintf(f,"\n");
	}
	end=clock();
    double time_use = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Time used %lf\n\n", time_use);
	fclose(f);
	return 1;
}
