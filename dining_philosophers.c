#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>
#include<string.h>
#include<unistd.h>
#include<math.h>
#include<stdlib.h>

sem_t cs[5];
enum {THINKING,HUNGRY,EATING}state[5];

void init()
{
	int i;
	for(i=0;i<5;i++)
	{
		state[i]=THINKING;
	}
}

void pickup(int i)
{
	state[i]=HUNGRY;
	printf("\nPhilosopher %d is Hungry",i);
	
	test(i);
	
	if(state[i]!=EATING)
		sem_wait(&cs[i]);
		
	if(state[i]==EATING)
	{
	
		printf("\n\t\tPhilosopher %d picks chopsticks %d and %d",i,i,(i+1)%5);
		printf("\n\t\tPhilosopher %d is eating",i);
	}
	
	sleep(rand()%3);
	
	
}

void putdown(int i)
{
	if(state[i]==EATING)
	{
	printf("\n\t\t\t\tPhilosopher %d putdown chopsticks %d and %d",i,i,(i+1)%5);
	state[i]=THINKING;
	
	printf("\n\t\t\t\tPhilosopher %d has finished eating",i);
	
	test((i+4)%5)
	test((i+1)%5)
	}
}

void test(int i)
{
	if(state[(i+4)%5]!=EATING && state[(i+1)%5]!=EATING && state[i]==HUNGRY)
	{
		state[i]=EATING;
		sem_post(&cs[i]);
	}
}	



void * philosopher(void *p)
{
	int i=*(int*)p;
	
	while(1)
	{
		
		pickup(i);
		putdown(i);
		
		sleep(rand()%5);
		
		
		
		
	}
}

int main()
{
	int i;
	init();
	for(i=0;i<5;i++)
		sem_init(&cs[i],0,1);
	
	pthread_t ph[5];
	
	for(i=0;i<5;i++)
	{
		int *p=(int*)malloc(sizeof(int));
		*p=i;
		
		pthread_create(&ph[i],NULL,philosopher,p);
	}
	
	for(i=0;i<5;i++)
	{
		pthread_join(ph[i],NULL);
	}
}
