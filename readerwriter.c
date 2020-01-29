#include<stdio.h>
#include<unistd.h>
#include<pthread.h>
#include<semaphore.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>


int x;
sem_t wrr,rc;
pthread_mutex_t m,wrt;

int rcount=0;



void* writer(void *p)
{
	int i=*(int*)p;
	while(1)
	{	
		printf("\t\t\tWriter %d trying to enter\n",i);
		sem_wait(&wrr);
		
		printf("\t\t\tWriter %d inside\n",i);
		x=rand()%100;
		printf("\t\t\tWriter %d wrote %d\n",i,x);
		sleep(20);
		
		printf("\t\t\tWriter %d left\n",i);
		sem_post(&wrr);
		
		sleep(rand()%3);
	}
}

void* reader(void *p)
{
	int i=*(int*)p;
	
	while(1)
	{
		sleep(10);
		printf("Reader %d trying to enter\n",i);
		pthread_mutex_lock(&m);
		printf("Reader %d inside\n",i);
		rcount++;
		
		if(rcount==1)
			sem_wait(&wrr);
		
		pthread_mutex_unlock(&m);
		
		
		sleep(rand()%3);
		printf("Reader %d read %d\n",i,x);
		
		pthread_mutex_lock(&m);
		
		rcount--;
		printf("Reader %d left\n",i);
		if(rcount==0)
		{	
			printf("Reader %d gives signal to writer\n",i);
			sem_post(&wrr);
		}
		
		pthread_mutex_unlock(&m);
		
		
		sleep(rand()%9);
	}
}
		
		
		

int main()
{
	sem_init(&wrr,0,1);
	sem_init(&rc,0,0);
	
	pthread_mutex_init(&m,NULL);
	pthread_mutex_init(&m,NULL);
	
	int m,n;
	
	scanf("%d%d",&m,&n);
	pthread_t rd[10],wr[10];
	
	int i;
	
	for(i=0;i<m;i++)
	{
		int *p=(int*)malloc(sizeof(int));
		*p=i;
		pthread_create(&rd[i],NULL,reader,p);
	}
	
	for(i=0;i<n;i++)
	{
		int *p=(int*)malloc(sizeof(int));
		*p=i;
		pthread_create(&wr[i],NULL,writer,p);
	}
	
	for(i=0;i<m;i++)
	{
		
		pthread_join(rd[i],NULL);
	}
	
	for(i=0;i<n;i++)
	{
		
		pthread_join(wr[i],NULL);
	}
	
}
