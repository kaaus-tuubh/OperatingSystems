#include<stdio.h>
#include<unistd.h>
#include<pthread.h>
#include<semaphore.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>


int x1;
sem_t rc,wc,z;
pthread_mutex_t m,wrt,x,y;

int rcount=0;
int wcount=0;



void* writer(void *p)
{
	int i=*(int*)p;
	while(1)
	{	
		printf("\t\t\tWriter %d trying to enter\n",i);
		
		pthread_mutex_lock(&x);
		printf("\t\t\tWriter %d inside\n",i);
		rcount++;
		
		if(rcount==1)
			sem_wait(&rc);
		
		pthread_mutex_unlock(&x);
		
		sem_wait(&wc);
		
		printf("\t\t\tWriter %d inside\n",i);
		x1=rand()%100;
		printf("\t\t\tWriter %d wrote %d\n",i,x1);
		sleep(2);
		
		sem_post(&wc);
		pthread_mutex_lock(&x);
		printf("\t\t\tWriter %d left\n",i);
		rcount++;
		
		
		
		if(wcount==0)
			sem_post(&rc);
		
		pthread_mutex_unlock(&x);
		
		sleep(rand()%5);
	}
}

void* reader(void *p)
{
	int i=*(int*)p;
	
	while(1)
	{
		
		printf("Reader %d trying to enter\n",i);
		
		sem_wait(&z);
		sem_wait(&rc);
		
		pthread_mutex_lock(&y);
		printf("Reader %d inside\n",i);
		rcount++;
		
		if(rcount==1)
			sem_wait(&wc);
		
		pthread_mutex_unlock(&y);
		
		sem_post(&rc);
		sem_post(&z);
		sleep(rand()%3);
		printf("Reader %d read %d\n",i,x1);
		
		pthread_mutex_lock(&y);
		
		rcount--;
		printf("Reader %d left\n",i);
		if(rcount==0)
		{	
			printf("Reader %d gives signal to writer\n",i);
			sem_post(&wc);
		}
		
		pthread_mutex_unlock(&y);
		
		
		sleep(rand()%9);
	}
}
		
		
		

int main()
{
	sem_init(&wc,0,1);
	sem_init(&z,0,1);
	sem_init(&rc,0,1);
	
	
	pthread_mutex_init(&x,NULL);
	pthread_mutex_init(&y,NULL);
	
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
