#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>

int main(int cnt,char *arr[])
{	
	int n;
	
	char temp[10];
	
	for(int i=1;i<cnt-1;i++)
	{
		for(int j=1;j<cnt-i;j++)
		{
			if(strcmp(arr[j],arr[j+1])>0)   // order  // if arr[j] comes after arr[j+1] move forward
			{
				strcpy(temp,arr[j]);
				strcpy(arr[j],arr[j+1]);
				strcpy(arr[j+1],temp);
			}
		}
	}
		printf("\nSorted Array:");
		for(int i=1;i<cnt;i++)
		{
			printf("%s",arr[i]);
		}
		
		printf("\nENter integer to execute execv:");
		scanf("%d",&n);
		execv("./s.out",arr);
}
