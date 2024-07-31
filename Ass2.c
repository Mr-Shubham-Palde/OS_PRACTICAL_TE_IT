#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/wait.h>

//Function to perform the bubble sort

void bubblesort(int arr[],int n)
{
	int temp;
	for(int i=0;i<n-1;i++)
	{
		for(int j=i+1;j<n;j++)
		{
			if(arr[i]>arr[j])
			{
				temp=arr[i];
				arr[i]=arr[j];
				arr[j]=temp;
			}
		}
	}
}

//function to perform the selection sort

void selectionsort(int arr[], int n)
{
	int temp,small;
	for(int i=0;i<n-1;i++)
	{
		small=i;
		for(int j=i+1;j<n;j++)
		{
			if(arr[small]>arr[j])
			{
				small=j;
			}
		}
		temp=arr[i];
		arr[i]=arr[small];
		arr[small]=temp;
	}
}

//main function
int main()
{
	int n;
	printf("Enter the number of elements:");
	scanf("%d",&n);
	
	int arr[n];//Original array
	
	printf("Enter array elements:");
	for(int i=0;i<n;i++)
	{
		scanf("%d",&arr[i]);
		
	}
	
	//Allocate Memory for the array copy
	int *arr_copy=(int *)malloc(n *sizeof(int));
	if(arr_copy==NULL)
	{
		printf("Memory allocation failed\n");
		return 1;
	}
	
	
	//copy of original array
	for(int i=0;i<n;i++)
	{
		arr_copy[i]=arr[i];
	}
	
	
	//creating the fork process
	pid_t pid = fork();
	
	if(pid<0)//no child process is get created
	{
		//fork failed
		perror("fork failed");
		free(arr_copy);
		return 1;
	}
	
	if(pid==0)//child process is get created successfullt
	{
		//child process
		printf("This is the child process(PID:%d)\n",getpid());
		bubblesort(arr_copy,n);
		printf("The sorted array in the child process is:\n");
		
		for(int i=0;i<n;i++)
		{
			printf("%d", arr_copy[i]);
			printf("\n");
		}
		printf("\n");
		
		//exit child process
		exit(0);
		
	}
	
	else//if(pid>0) parent process is get executed successfully
	{
		// parent process
		printf("This is parent process(PID:%d)\n",getpid());
		
		//wait for child process to complete
		printf("Parent Process is waiting for the child process...\n");
		wait(NULL);
		
		//perform Selection sort
		selectionsort(arr,n);
		printf("The Sorted array in the parent  process is:\n");
		for(int i=0;i<n;i++)
		{
			printf("%d",arr[i]);
			printf("\n");
		}
		printf("\n");
			
		printf("Parent process sleeping to demonstrate the zombie state....\n");
		sleep(15);
		
		printf("Parent process Waking up from Sleep....\n");
	
		
		
	}
	free(arr_copy);
	return 0;
}
