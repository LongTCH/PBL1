#include <stdio.h>
#include <conio.h>
#include "constant.h"
#include <stdlib.h>
int checkinput1(char *s)
{
	int t=0,k[2]={1,1};
	while (s[t]!='\0') 
	{
		if (s[t]=='-') 
		{
			if (t>0) return 0;
			k[0]--;
		}
		if (s[t]=='.') k[1]--;
		if (k[0]<0 || k[1]<0) return 0;
		t++;
	}
	if (t==0) return 0;
	if (t==1 && k[0]*k[1]==0) return 0;
	return 1;
}

int EnterMatrix(FILE *f)
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
	int n;
	char temp;
	char str[101];
	double cost;
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
	
	for (int i=1; i<=n; i++)
	{
		for (int j=1; j<=n; j++)
    	{
    		if (i==j) fprintf(f,"%d ",0);
    		else 
    		{
				printf("Is there a direct path from %d to %d? Press 'y'(yes) or 'o'(no)",i,j);
				fflush(stdin);
				do
				{
					check=getch();
				} while (check!='y' && check!='o');
				
				if (check=='y')
				{
					printf("\r");
			    	printf("                                                             ");
			    	printf("\r");
					do
			    	{
			    		printf("Enter direct cost from %d to %d: ",i,j);
			    		fflush(stdin);
			    		if (scanf("%100[-.0-9]s",str)==0) printf(ERR);
			    		else 
						{
							scanf("%c",&temp);
							if (temp!='\n' || checkinput1(str)==0) printf(ERR);
			    	    	else break;
						}
			    	} while (1);
			    	cost = atof(str);
					fprintf(f,"%.16lf ",cost);				
				} else 
				{
					printf("\r");
			    	printf("                                                             ");
			    	printf("\r");
					printf("No direct path from %d to %d\n",i,j);
					fprintf(f,"%.0e ",MAXC);
				}
		    }
		}
    	fprintf(f,"\n");
	}
	fclose(f);
	return 1;
}
