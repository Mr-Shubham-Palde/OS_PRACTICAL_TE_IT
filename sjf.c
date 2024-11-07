#include<stdio.h>
#include<stdlib.h>
#define MAX_PROCESSES 10

int main(){
    int arrival_t[MAX_PROCESSES],burst_t[MAX_PROCESSES],temp[MAX_PROCESSES];
    int remaining_t[MAX_PROCESSES];
    int completion_t[MAX_PROCESSES], turnaround_t[MAX_PROCESSES], waiting_t[MAX_PROCESSES];
    int smallest,i,limit,count=0,time;
    int total_wait_time,total_turnaround_time;
    float averagetat,averagewt;

    printf("Enter the no of processes(MAX %d):",MAX_PROCESSES);
    scanf("%d",&limit);

    if(limit>MAX_PROCESSES){
        printf("The no of processes are greater than the max");
    }

    printf("Enter data for %d processes",limit);
    for(i=0;i<limit;i++){
        printf("For process %d",i+1);
        printf("\nEnter the arrival time:");
        scanf("%d",&arrival_t[i]);
        printf("\nEnter the burst time:");
        scanf("%d",&burst_t[i]);
        remaining_t[i]=burst_t[i];
        temp[i]=burst_t[i];
    }

    int complete[MAX_PROCESSES]={0};// to check whether the process has been completed or not

    for(time=0;count!=limit;time++){
        smallest=-1;
        for(i=0;i<limit;i++){
            if(arrival_t[i]<=time && !complete[i]){
                if(smallest==-1 || remaining_t[i]<remaining_t[smallest]){
                    smallest=i;
                }
            }
        }

        if(smallest!=-1){
            remaining_t[smallest]--;
            if(remaining_t[smallest]==0){
                count++;
                complete[smallest]=1;
                completion_t[smallest]=time+1;
                waiting_t[smallest]=completion_t[smallest]-arrival_t[smallest]-temp[smallest];
                turnaround_t[smallest]= completion_t[smallest]-arrival_t[smallest];
                total_wait_time+=waiting_t[smallest];
                total_turnaround_time+= turnaround_t[smallest];

            }

        }
    }

    averagetat=(float)total_turnaround_time/limit;
    averagewt=(float)total_wait_time/limit;

    printf("\nProcess no \t AT\tBT\tCT\tWT\tTAT\n");
    for(i=0;i<limit;i++){
        printf("%d\t\t%d\t%d\t%d\t%d\t%d\n",i+1,arrival_t[i],temp[i],completion_t[i],waiting_t[i],turnaround_t[i]);
    }

    printf("Average waitinig time:",averagetat);
    printf("Average turnaround time:",averagewt);

    return 0;


}