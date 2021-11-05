//
//  main.c
//  Project1
//
//  Created by Nima $wagaram on 11/1/21.
//  Copyright © 2021 Nima $wagaram. All rights reserved.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Process{
    int PID;
    int burstTime;
    int priority;
};

struct ProcessInfo{
    int PID;
    int totalBurstTime;
    int priority;
    int waitingTime;
    int responseTime;
    int turnAroundTime;
    int pCtr;
};



void getTimeInfos(struct Process processQueue[],struct ProcessInfo array[], int numProcesses, int numPIDs){
    int totalContextSwitches = 0;
    int voluntarySwitches = 0;
    int nonVoluntarySwitches;
    int x = 0;
    int y = 0;
    int pFlag = 0;
    int prevID = 0;
    while(x < numPIDs){
        y = 0;
        pFlag = 0;
        while(y < numProcesses && array[x].pCtr > 0){
            if (processQueue[y].PID != prevID){
                totalContextSwitches += 1;
                prevID = processQueue[y].PID;
            }
            if (processQueue[y].PID == array[x].PID){
                if (pFlag == 0)
                    pFlag = 1;
                array[x].pCtr -= 1;
                continue;
             }
            if(array[x].pCtr == 0){
                voluntarySwitches += 1;
            }
            
            if (pFlag != 1)
                array[x].responseTime += processQueue[y].burstTime;
            array[x].waitingTime += processQueue[y].burstTime;
            y++;
    }
        x++;
}
    nonVoluntarySwitches = totalContextSwitches - voluntarySwitches;
    int allBurstTimes = 0;
    int avgThroughput = 0;
    int avgTurnAroundTime = 0;
    int avgWaitingTime = 0;
    int rTime = 0;
    for(int a =0; a < numPIDs;a++){
        allBurstTimes += array[a].totalBurstTime;
        avgTurnAroundTime += array[a].waitingTime + array[a].totalBurstTime;
        avgWaitingTime += array[a].waitingTime;
        rTime += array[a].responseTime;
    }
     avgThroughput = numPIDs / allBurstTimes;
     avgTurnAroundTime /= numPIDs;
     avgWaitingTime /= numPIDs;
     rTime /= numPIDs;
  
       printf("%d\n", nonVoluntarySwitches);                               //nonVoluntary
       printf("100.0\n");                                  //CPU Utilization
       printf("%0.02f",avgThroughput);                        //Throughput
       printf("%0.02f",avgTurnAroundTime);                         //TurnAround
       printf("%0.02f", avgWaitingTime);                          //WaitingTime
       printf("%0.02f", rTime);                          //rTime
    
    // return nonVoluntarySwitches,avgThroughput,avgTurnAroundTime,avgWaitingTime,rTime;
}



int main(int argc, char * argv[]) {
    
    int start;
    int numPIDs;
    int numProcesses;
    FILE* fp;
    if (argc < 1) {
        fp = fopen(argv[1],"r");
       
    }
    else {
         fp = stdin;
    }
    fscanf(fp,"%d", &start);
    fscanf(fp,"%d", &numPIDs);
    fscanf(fp,"%d", &numProcesses);
    
    struct ProcessInfo* arrayStore = malloc(numPIDs*sizeof(arrayStore));
    struct Process* processQueue = malloc(numProcesses*sizeof(processQueue));

    int a;
    for(a =0; a<numProcesses; ++a ){
        fscanf(fp,"%d %d %d", &processQueue[a].PID, &processQueue[a].burstTime,&processQueue[a].priority);
        arrayStore[processQueue[a].PID-1].totalBurstTime += processQueue[a].burstTime;
        arrayStore[processQueue[a].PID-1].pCtr += 1;
   }

    printf("%d\n",numPIDs);                       //Gets voluntary context switch
 
    
    getTimeInfos(processQueue, arrayStore, numProcesses, numPIDs);
    
    return 0;
    }
    




