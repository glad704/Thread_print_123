/*************************************************************************
 * FILE		: print_123_repeatedly_using_thread().c
 * DESCRIPTION	: Program to print 123 repeatedly using thread
 * AUTHOR	: GLADSON HANSDA
 * DATED	: 21/07/2020
 * **********************************************************************/

#include<stdio.h>
#include<pthread.h>

pthread_cond_t cond1 = PTHREAD_COND_INITIALIZER;
pthread_cond_t cond2 = PTHREAD_COND_INITIALIZER;
pthread_cond_t cond3 = PTHREAD_COND_INITIALIZER;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

int value=1;

void* foo(void* n)
{
	while(1)
	{
		pthread_mutex_lock(&lock);
		if(value!=(int)*(int*)n)
		{
			if((int)*(int*)n==1)
			{
				pthread_cond_wait(&cond1,&lock);
			}
			else if((int)*(int*)n==2)
			{
				pthread_cond_wait(&cond2,&lock);
			}
			else
			{
				pthread_cond_wait(&cond3,&lock);
			}
		}

		printf("%d ",*(int*)n);
		if(value==3)
		{
			value=1;
			pthread_cond_signal(&cond1);
		}
		else if(value==1)
		{
			value=2;
			pthread_cond_signal(&cond2);
		}
		else if(value==2)
		{
			value=3;
			pthread_cond_signal(&cond3);
		}
		pthread_mutex_unlock(&lock);
	}
	return NULL;
}

int main()
{
	pthread_t tid1,tid2,tid3;
	int n1=1,n2=2,n3=3;
	
	pthread_create(&tid1,NULL,foo,(void*)&n1);
	pthread_create(&tid2,NULL,foo,(void*)&n2);
	pthread_create(&tid3,NULL,foo,(void*)&n3);
	for(int i=0;i<100000000000;i++);
	return 0;
}
