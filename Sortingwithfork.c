#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
void merge(int A[50],int low,int mid,int high,int n);
void merge_sort(int A[50],int low,int high,int n);
void swap(int* a, int* b);
int partition (int arr[], int low, int high);
void quickSort(int arr[], int low, int high);

void main()
{
int array[50];
int n,k;
printf("Enter No. of Integers to be sorted\n");
scanf("%d",&n);
printf("enter the integers to be sorted:\n");
for(int i=0;i<n;i++)
	scanf("%d",&array[i]);


for(int i=0;i<n;i++)
	printf("%d\t",array[i]);
printf("\n");
pid_t childpid;


printf("I am parent %d\n",getpid());

//Forking

printf("ENTER:\n1. ZOMBIE PROCESS\n2. ORPHAN PROCESS\n3. EXIT\n");
scanf("%d",&k);
switch(k){
	case 1:
	{
		childpid = fork();		//Forking
		if(childpid == -1)
			printf("fork failed\n");

//child	
		else if(childpid==0){
			printf("I am child %d \tmy parent id is %d \n",getpid(),getppid());
			merge_sort(array,0,n-1,n);
			
		}
	
//Return in parent
		else{
			system("wait");
			printf("i am in parent %d\n",getpid());
			quickSort(array, 0, n-1);
			printf("quick sorted array\n");
			for(int i=0;i<n;i++)
				printf("%d, ",array[i]);
				
			printf("\n");
			sleep(10); //creating zombie
			
			}
			break;
		}
	case 2:
	{
		childpid = fork();		//Forking
		if(childpid == -1)
			printf("fork failed\n");

//child	
		else if(childpid==0){
			printf("I am child %d \tmy parent id is %d \n",getpid(),getppid());
			merge_sort(array,0,n-1,n);
			sleep(10); //creating orphan
			printf("I am orphan\n");
	}
	
//Return in parent
		else{
			printf("i am in parent %d\n",getpid());
			quickSort(array, 0, n-1);
			printf("quick sorted array\n");
			for(int i=0;i<n;i++)
				printf("%d, ",array[i]);
				
			printf("\n");
			
		}
		break;
	}
}


}

void merge(int A[50],int low,int mid,int high,int n)
{
	int i=low,j=mid+1,k=low,comp_no=0,m, it_no=0;
	int temp[50];
	it_no++;
	while(i<=mid && j<=high)
	{
		if(A[i]<=A[j])
		{
			temp[k]=A[i];
			i++;
			k++;
			comp_no++;
		}
		else
		{
			temp[k]=A[j];
			j++;
			k++;
			comp_no++;
		}
	}
	while(j<=high)
	{
		temp[k]=A[j];
		j++;
		k++;
		comp_no++;
	}
	
	
	while(i<=mid)
	{
		temp[k]=A[i];
		i++;
		k++;
		comp_no++;
	}
	for(i=low;i<=high;i++)
	{
		A[i]=temp[i];
	}
	printf("\n\nIteration number : %d",it_no);
	printf("\nNumber of comparisons : %d",comp_no);
	printf("\nThe numbers are arranged currently as : (");
	for(m=0;m<n;m++)
	{
		printf("%d,",A[m]);
	}
	printf(")\n");
}

void merge_sort(int A[50],int low,int high,int n)
{
	int mid;
	if(low<high)
	{
		mid=(low+high)/2;
		merge_sort(A,low,mid,n);
		merge_sort(A,mid+1,high,n);
		merge(A,low,mid,high,n);
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

