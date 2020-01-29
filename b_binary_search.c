#include<stdio.h>
#include<stdlib.h>
#include<string.h>
void binarySearch(int array[],int left, int right, int key);
void main(int argc, char *argv[]){
	
	int array[50];
	int i=1,n=argc, key;
	printf("enter value to be searched: ");
	scanf("%d",&key);
	for(i=1;argv[i]!=NULL;i++)
		array[i] = atoi(argv[i]);
	
	binarySearch(array, 1,n+1,key);
}


void binarySearch(int array[],int left, int right, int key){
	
	if(left<=right){
	
	int mid = (left + right)/2;
	
	//int v = key-array[mid];
	
	if(array[mid]==key){
		printf("value %d found at location %d\n",key, mid);
		return;
	}

	else if(array[mid]<key){
		binarySearch(array,mid+1,right, key);
	}
	
	else if(array[mid]>key) {
		binarySearch(array, left, mid-1, key);
	}	
}
	else{
		printf("value %d not found\n",key);
	}		
}

