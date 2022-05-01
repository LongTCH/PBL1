#include <stdio.h>
#include <conio.h>
#include "constant.h"
void EnterMatrix(FILE *f)
{
	char check;
	printf("Are you sure to generate a new matrix?\nThe exist one will be deleted!\nPress 'y'(if yes) or 'o'(if no)\n");
	do
	{
		fflush(stdin);
		check=getch();
	} while (check != 'y'  && check != 'o');
	if (check=='o') return;
	f=fopen(LINK,"w");
	int n;
	char temp;
	double cost;
	do
	{
		fflush(stdin);
		printf("Enter number of vertices: "); 
		if (scanf("%d%c",&n,&temp)!=2 || temp!= '\n' || n<=0) printf(ERR);
		else break;
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
			    		if (scanf("%lf%c",&cost,&temp)!=2 || temp!='\n') printf(ERR);
			    		else break;
			    	} while (1);
					fprintf(f,"%.2lf ",cost);				
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
}
