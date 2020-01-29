#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include<semaphore.h>

int q[100];
int f=0,r=0;

sem_t empty,full;
pthread_mutex_t m;



void* prod(void *p)
{
	int i=*(int*)p;
	
	while(1)
	{
		int x=rand()%20;
		sem_wait(&empty);
		pthread_mutex_lock(&m);
		
		sleep(rand()%3);
		q[r]=x;
		r;
		for(int i=f;i<=r;i++)
		{
			printf("%d ",q[i]);
		}
		printf("\nProducer %d produced %d\n",i,q[r]);
		r++;
		
		pthread_mutex_unlock(&m);
		sem_post(&full);
		
		sleep(rand()%5);
			
	
	}
}

void* cons(void *p)
{
	int i=*(int*)p;
	
	while(1)
	{
		sem_wait(&full);
		pthread_mutex_lock(&m);
		
		sleep(rand()%3);
		int x=q[f];
		
		printf("\t\t\t");
		
		printf("\n\t\t\tConsumer %d consumed %d\n",i,x);
		f++;
		for(int i=f;i<=r-1;i++)
		{
			printf("%d ",q[i]);
		}
		
		pthread_mutex_unlock(&m);
		sem_post(&empty);
		
		sleep(rand()%5);
	
	}
}

int main()
{
	
	sem_init(&empty,0,100);
	sem_init(&full,0,0);
	
	pthread_mutex_init(&m,NULL);
	
	int m,n;
	
	scanf("%d%d",&m,&n);
	
	pthread_t pr[10],co[10];
	
	int i,j;
	
	for(i=0;i<m;i++)
	{
		int *p=(int*)malloc(sizeof(int));
		*p=i;
		
		pthread_create(&pr[i],NULL,prod,(void*)p);
	}
	
	for(i=0;i<n;i++)
	{
		int *p=(int*)malloc(sizeof(int));
		*p=i;
		
		pthread_create(&pr[i],NULL,cons,(void*)p);
	}
	
	for(i=0;i<m;i++)
	{
		pthread_join(pr[i],NULL);
	}
	
	for(i=0;i<n;i++)
	{
		pthread_join(co[i],NULL);
	}
}
