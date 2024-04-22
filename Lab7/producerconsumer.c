#include<stdio.h>
#include<stdlib.h>
#include<semaphore.h>
#include<pthread.h>
#define max 10
int buffersize;
int buffer[max];
int in=0;
int out=0;
sem_t empty,full;
pthread_t producerthread,consumerthread;
pthread_mutex_t mutex=PTHREAD_MUTEX_INITIALIZER;
void *producer()
{
        int i;
        while(i!=buffersize)
        {
        sem_wait(&empty);
        pthread_mutex_lock(&mutex);
        printf("producer produced %d\n",i+1);
        buffer[in]=i+1;
        in=(in+1)%buffersize;
        sem_post(&full);
        pthread_mutex_unlock(&mutex);
        i++;
        }
        pthread_exit(NULL);
}
void *consumer()
{
        int i;
        while(i!=buffersize)
        {
                sem_wait(&full);
                pthread_mutex_lock(&mutex);
                printf("Consumer consumed %d\n",buffer[out]);
                out=(out+1)%buffersize;
                sem_post(&empty);
                pthread_mutex_unlock(&mutex);
                i++;
        }
        pthread_exit(NULL);
}




void main()
{
        printf("Enter the number of items in the buffer");
        scanf("%d",&buffersize);
        sem_init(&empty,0,buffersize);
        sem_init(&full,0,0);
        pthread_create(&producerthread,0,producer,0);
        pthread_create(&consumerthread,0,consumer,0);
        pthread_join(producerthread,0);
        pthread_join(consumerthread,0);
        sem_destroy(&full);
        sem_destroy(&empty);
}de
