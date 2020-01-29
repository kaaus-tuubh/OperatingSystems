#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>


void multiply(int m1,int n1,int m2,int n2,int A[10][10],int B[10][10],int ans[][10])
{
	int i,j,k,sum;
	
	for(i=0;i<m1;i++)
	{
		for(j=0;j<n2;j++)
		{	
			sum=0;
			for(k=0;k<n1;k++)
			{
				sum+=A[i][k]*B[k][j];
			}
			
			ans[i][j]=sum;
		}
	}
}

void show(int m1,int n2,int ans[10][10])
{
	int i,j;
	for(i=0;i<m1;i++)
	{
		for(j=0;j<n2;j++)
		{
			printf("%d\t",ans[i][j]);
		}
		printf("\n");
	}
}	

void* thread_mul(void *p)
{
	int **arr=(int**)p;
	
	int i,j,sum=0;
	int *A=arr[1];
	int *B=arr[2];
	int n1=arr[0][0];
	for(i=0;i<n1;i++)
	{
		sum+=A[i]*B[i];
		//sum+=(*(arr+(1*n1)+i)) * (*(arr+(2*n1)+i));
	}
	
	
	int *q=(int *)malloc(sizeof(int));
	*q=sum;
	
	pthread_exit(q);
}
				
int main()
{
	int A[10][10],B[10][10],ans[10][10];
	
	int m1,n1,m2,n2;
	
	clock_t t;
	double tk=0;
	
	scanf("%d%d%d%d",&m1,&n1,&m2,&n2);
	
	pthread_t th[10][10];
	
	int i,j,k;
	for(i=0;i<m1;i++)
	{
		for(j=0;j<n1;j++)
		{
			scanf("%d",&A[i][j]);
		}
	}
	
	for(i=0;i<m2;i++)
	{
		for(j=0;j<n2;j++)
		{
			scanf("%d",&B[i][j]);
		}
	}
	
	
	for(i=0;i<m1;i++)
	{
		for(j=0;j<n1;j++)
		{
			printf("%d\t",A[i][j]);
		}
		printf("\n");
	}
	show(m1,n1,A);
	show(m2,n2,B);
	int ch;
	
	
	do
	{
		scanf("%d",&ch);
		switch(ch)
		{
			case 1:t=clock();
				multiply(m1,n1,m2,n2,A,B,ans);
				show(m1,n2,ans);
				t=clock()-t;
				tk=((double)t)/CLOCKS_PER_SEC;
				printf("%f\n",tk);
				break;
				
			case 2:
				t=clock();
				for(i=0;i<m1;i++)
				{
					for(j=0;j<n2;j++)
					{
						int **ptr=(int**)malloc(3*sizeof(int));
						ptr[0]=(int*)malloc(sizeof(int));
						ptr[1]=(int*)malloc(n1*sizeof(int));
						ptr[2]=(int*)malloc(n1*sizeof(int));
						ptr[0][0]=n1;
						for(k=0;k<n1;k++)
						{
							ptr[1][k]=A[i][k];
							
						}
						for(k=0;k<m2;k++)
						{
							ptr[2][k]=B[k][j];
						}
						
						pthread_create(&th[i][j],NULL,thread_mul,(void*)ptr);
					}
				}
				
				for(i=0;i<m1;i++)
				{
					for(j=0;j<n1;j++)
					{
						void * status;
						pthread_join(th[i][j],&status);
			
						ans[i][j]=*(int*)status;
					}
				}
				
				show(m1,n2,ans);
				
				t=clock()-t;
				tk=((double)t)/CLOCKS_PER_SEC;
				printf("%f\n",tk);
				
				break;
			case 3:ch=0;
		}
	}while(ch!=0);
	
}

						
						
						
