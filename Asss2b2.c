#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>

int main(int cnt,char *arr[])
{
	printf("This is second process %d",getpid());
	printf("\nReversed array:\n");
	for(int i=cnt-1;i>=1;i--){
		printf("\n%s",arr[i]);
	}
}
