#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<semaphore.h>
#include<unistd.h>
#define maxsize 20
typedef struct{
    int in,out;
    int list[maxsize];
    sem_t full;
    sem_t emp;
    pthread_mutex_t lock;
}Itemlist;
Itemlist A;
int item,size;
void *prod(void *arg);
void *cons(void *arg);
void init();
void main(){
    int i,np,nc;
    init();
    pthread_t pd[5],cd[5];
    printf("\n Enter the no of producers:");
    scanf("%d",&np);
    printf("\Enter the no of customers:");
    scanf("%d",&nc);
    printf("\nHow many items to be produced:");
    scanf("%d",&size);
    for(i=0;i<np;i++){
        int *arg=malloc(sizeof(int*));
        *arg=i;
        pthread_create(&pd[i],NULL,prod,arg);
        printf("\nProducer thread %d has been created:",i+1);
    }
    for(i=0;i<nc;i++){
        int *arg=malloc(sizeof(int*));
        *arg=i;
        pthread_create(&cd[i],NULL,cons,arg);
        printf("\nConsumer thread %d has been created:",i+1);
    }
    for(i=0;i<np;i++){
       
        pthread_join(pd[i],NULL);
        printf("\nProducer thread %d has been Finished:",i+1);
    }
     for(i=0;i<nc;i++){
       
        pthread_join(cd[i],NULL);
        printf("\nConsumer thread %d has been Finished:",i+1);
    }
}

void *prod(void *arg){
    int i=*(int*)arg;
    while(item<size+1){
        sem_wait(&A.emp);
        pthread_mutex_lock(&A.lock);
        printf("\nProducer %d has produced an item %d",i+1,item);
        A.list[(A.in++)%maxsize]=item++;
        pthread_mutex_unlock(&A.lock);
        sem_post(&A.full);
        sleep(2);
    }
}

void *cons(void *arg){
    int i=*(int*)arg;
    while(1){
        sem_wait(&A.full);
        pthread_mutex_lock(&A.lock);
        printf("\ncustomer %d has produced an item %d",i+1,A.list[(A.out++)%maxsize]);
        pthread_mutex_unlock(&A.lock);
        sem_post(&A.emp);
       

}
}
void init()
{
    A.in=0,A.out=0;
    sem_init(&A.full,0,0);
    sem_init(&A.emp,0,maxsize);
    item=1;
    pthread_mutex_init(&A.lock,NULL);
}