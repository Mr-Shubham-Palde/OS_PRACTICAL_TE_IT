#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<semaphore.h>
#include<unistd.h>
pthread_mutex_t rwmutex;
pthread_mutex_t lock;
pthread_t thread;
int r,w,rdcnt;
void *reader(void *arg);
void *writer(void *arg);
void init();

void main(){
    int i;
    init();
    printf("\n Enter the number of readers:");
    scanf("%d",&r);
    printf("\nEnter the no of writer:");
    scanf("%d",&w);

    for(i=0;i<w;i++){
        int *arg=malloc(sizeof(int*));
        *arg=i;
        pthread_create(&thread,NULL,writer,arg);
    }

     for(i=0;i<r;i++){
        int *arg=malloc(sizeof(int*));
        *arg=i;
        pthread_create(&thread,NULL,reader,arg);
    }

     for(i=0;i<w;i++){
        
        pthread_join(thread,NULL);

    }
     for(i=0;i<r;i++){
        
        pthread_join(thread,NULL);
        
    }
}

void init(){
    pthread_mutex_init(&lock,NULL);
    pthread_mutex_init(&rwmutex,NULL);
    rdcnt=0;
}

void *reader(void *arg){
    int i=*(int *)arg;
    int cnt=0;
    printf("\nReader %d is trying to read",i+1);
    pthread_mutex_lock(&lock);
    rdcnt++;
    if(rdcnt==1)
        pthread_mutex_lock(&rwmutex);
    printf("\nreader %d is reading",i+1);
    pthread_mutex_unlock(&lock);
    sleep(3);
    pthread_mutex_lock(&lock);
    rdcnt--;
    if(rdcnt==0)
        pthread_mutex_lock(&rwmutex);
    pthread_mutex_unlock(&lock);
    printf("\nreader %d is leaving",i+1);
}

void *writer(void *arg){
    int i=*(int*)arg;
    printf("\nwriter %d is trying to rite",i+1);
    pthread_mutex_lock(&rwmutex);
    printf("\nwriter %d is writer",i+1);
    sleep(3);
    pthread_mutex_unlock(&rwmutex);
    printf("writer %d is leaving",i+1);
}

