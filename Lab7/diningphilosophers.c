#include<stdio.h>
#include<stdlib.h>
#include<semaphore.h>
#include<pthread.h>
#include<unistd.h>
#define N 5
sem_t forks[N];
pthread_mutex_t mutex=PTHREAD_MUTEX_INITIALIZER;
void *philosopher(void *arg)
{
        int id=*(int*)arg;
        int left=id;
        int right=(id+1)%N;
        printf("Philosopher is thinking");
        sleep(1);
        pthread_mutex_lock(&mutex);//mutual exclusion when forks are picked so deadlock doesn't occur
        printf("bkl philosopher abb khaega\n");
        sem_wait(&forks[left]);
        sem_wait(&forks[right]);
        pthread_mutex_unlock(&mutex);
        printf("Philosopher kha raha hai");
        sleep(2);
        sem_post(&forks[right]);
        sem_post(&forks[left]);
        pthread_exit(NULL);

}
int main()
{
        int i=0;
        int id[N];
        pthread_t philosophers[N];
        for(i=0;i<N;i++)
        {
                sem_init(&forks[i],0,1);
        }
        for(i=0;i<N;i++)
        {
                id[i]=i+1;
        }
        for(i=0;i<N;i++)
        {
                pthread_create(&philosophers[i],0,philosopher,&id[i]);
        }
        for(i=0;i<N;i++)
        {
                pthread_join(philosophers[i],NULL);
        }
        for(i=0;i<N;i++)
        {
                sem_destroy(&forks[i]);
        }
}
