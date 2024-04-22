#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<semaphore.h>
int readcount=0;
sem_t writing,reading;
int r,w;
void *reader()
{
        sem_wait(&reading);
        readcount++;
        if(readcount==1)
                sem_wait(&writing);
        sem_post(&reading);
        printf("reader  at work");
        sem_wait(&reading);
        printf("Reader  exiting \n");
        readcount--;
        sem_post(&reading);
        if(readcount==0)
                sem_post(&writing);

        pthread_exit(NULL);
}
void *writer()
{
        sem_wait(&writing);
        printf("Writer  writing \n");
        printf("Writer  exiting \n");
        sem_post(&writing);

        pthread_exit(NULL);

}




int main()
{
        int  i;
        printf("Enter the number of writers");
        scanf("%d",&w);
        printf("Enter the number of readers");
        scanf("%d",&r);
        pthread_t readers[r];
        pthread_t writers[w];
        sem_init(&writing,0,1);
        sem_init(&reading,0,1);
        for(i=0;i<r;i++)
        {
        pthread_create(&readers[i],0,reader,0);
        }
        for(i=0;i<w;i++)
        {
        pthread_create(&writers[i],0,writer,0);
        }
        for(i=0;i<w;i++)
        {
                pthread_join(writers[i],NULL);
        }
        for(i=0;i<r;i++)
        {
                pthread_join(readers[i],NULL);
        }
        sem_destroy(&reading);
        sem_destroy(&writing);
}
