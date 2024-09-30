#include<stdio.h>

int main()
{
	int p,r,i,j,flag;
	int avail_r[10];
	int allocated_r[10][20];
	int max_r[10][20];
	int need[10][20];
	
	
	printf("Enter the no of processes:");
	scanf("%d",&p);
	
	printf("Enter the no of resources:");
	scanf("%d",&r);
	
	printf("Available resources:\n");
	for (j=0;j<r;j++)
	{
		{
			printf("Enter data in [%d]:",j);
			scanf("%d",&avail_r[j]);
		}
		
	}
	printf("Display Array:\n");
	for(i=0;i<r;i++)
	{
		printf("%d\t",avail_r[i]);
		printf("\n");
	}
	
	printf("Allocated Resources:\n");
	for(i=0;i<p;i++)
	{
		for(j=0;j<r;j++)
		{
			printf("Enter data in[%d][%d]:",i,j);
			scanf("%d",&allocated_r[i][j]);
		}
	}
	
	printf("Display Matrix:\n");
	for(i=0;i<p;i++)
	{
		for(j=0;j<r;j++)
		{
			printf("%d\t",allocated_r[i][j]);
			
		}
		printf("\n");
	}
	
	printf("Max Resources:\n");
	
	for(i=0;i<p;i++)
	{
		for(j=0;j<r;j++)
		{
			printf("Enter data in [%d][%d]:",i,j);
			scanf("%d",&max_r[i][j]);
		}
	}
	
	printf("Display Matrix:\n");
	for(i=0;i<p;i++)
	{
		for(j=0;j<r;j++)
		{
			printf("%d\t",max_r[i][j]);
		}
		printf("\n");
	}
	
	printf("Need Matrix:\n");
	for(i=0;i<p;i++)
	{
		for(j=0;j<r;j++)
		{
			need[i][j]= max_r[i][j] - allocated_r[i][j];
			printf("%d\t",need[i][j]);
		}
		
	}
	
	int exe[10];
	for(i=0;i<p;i++)
	{
		exe[i]=0;
	}
	
	while(1)
	{
		for(i=0;i<p;i++)
		{
			if(exe[i]==0)
			{
				flag=1;
				for(j=0;j<r;j++)
				{
					if(avail_r[j]<need[i][j])
					{
						flag=0;
						break;
					}
				}
				if(flag==1)
				{
					printf("\n%d is running\n",i);
					exe[i]=1;
					for(j=0;j<r;j++)
					{
						avail_r[j]+= allocated_r[i][j];
					}
					break;
				}
			}
		}
		if(i==p)
		{
			flag=1;
			for(i=0;i<p;i++)
			{
				if(exe[i]==0)
				{
					flag=0;
					break;
				}
			}
			if(flag==1)
			{
				printf("Safe State");
			
			}
			else
			{
				printf("Not Safe");
			}
			break;
		}
	}
	return 0;
	
	
}
