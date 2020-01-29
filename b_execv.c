#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>

void swap(int* a, int* b) ;
int partition (int arr[], int low, int high);
void quickSort(int arr[], int low, int high);
void main()
{
	int array[50];
	char *buff[20];
	int n,k;
	printf("Enter No. of Integers to be sorted\n");
	scanf("%d",&n);
	printf("enter the integers to be sorted:\n");
	for(int i=0;i<n;i++)
		scanf("%d",&array[i]);
	
	for(int i=0;i<=n;i++){
		buff[i]=(char*)malloc(10);
	}
	pid_t childpid;

	printf("I am parent %d\n",getpid());
	
	childpid = fork();
	
	
	if(childpid == -1)
		printf("fork failed\n");
		
	if(childpid>0){
	
		printf("back in parent %d\n",getpid());
		
		quickSort(array,0,n-1);
		
		for(int i=0;i<n;i++)
			printf(" %d",array[i]);
		printf("\n");
		wait(NULL);
	}	
		
	if(childpid == 0){
		printf("Child Process\n");
		printf("Id: %d\n",getpid());
		
		int i=0;
		buff[0]="./b_binary_search";
		printf("a");
		for(i=1;i<=n;i++)
			sprintf(buff[i],"%d",array[i-1]);
		buff[i]=NULL;
		execv("./b_binary_search", buff);
		
		printf("child end");
	}
	

}


void swap(int* a, int* b) 
{ 
	int t = *a; 
	*a = *b; 
	*b = t; 
} 


int partition (int arr[], int low, int high) 
{ 
	int pivot = arr[high]; 
	int i = (low - 1); 

	for (int j = low; j <= high- 1; j++) 
	{ 
		
		if (arr[j] <= pivot) 
		{ 
			i++; 
			swap(&arr[i], &arr[j]); 
		} 
	} 
	swap(&arr[i + 1], &arr[high]); 
	return (i + 1); 
} 


void quickSort(int arr[], int low, int high) 
{ 
	if (low < high) 
	{ 
	
		int pi = partition(arr, low, high); 

		
		quickSort(arr, low, pi - 1); 
		quickSort(arr, pi + 1, high); 
	} 
} 



