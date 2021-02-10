#include "types.h"
#include "stat.h"
#include "user.h"
#include "param.h"

int main()
{
    int originalParentID = getpid();
    int childNumber = 0;

    int CBTs[30] = {0};
    int waitingTimes[30] = {0};
    int turnAroundTimes[30] = {0};
    int priorities[30] = {0};

    int policy = changePolicy(2);    //scheduleType 2 is priority scheduler
    printf(1, "*** policy %d(prioritySchedule) ***\n", policy);

    for (int i = 0; i < 30; i++)
    {
        if (fork() == 0)    //child process
        {
            wait();
            childNumber = i + 1;
            int priority;
            if (i < 5)
                priority = 6;
            if (i >= 5 && i < 10)
                priority = 5;
            if (i >= 10 && i < 15)
                priority = 4;
            if (i >= 15 && i < 20)
                priority = 3;
            if (i >= 20 && i < 25)
                priority = 2;
            if (i >= 25 && i < 30)
                priority = 1;

            setPriority(priority);
            printf(1, "** PID is %d, priority: %d **", getpid(), priority);
            break;
        } 
    }

    
    if (originalParentID == getpid())
    {   wait();
        //CWTPtimes is array: [0]: CBT, [1]: waitingTimes, [2]: turnAroundTimes
        //[3]: priority, [4]: process pid
        int *CWTPTimes = malloc(5 * sizeof(int));
        childNumber = 0;
        while (waitForPrioritySchedule(CWTPTimes) > 0)
        {
            CBTs[childNumber] = CWTPTimes[0];
            waitingTimes[childNumber] = CWTPTimes[1];
            turnAroundTimes[childNumber] = CWTPTimes[2];
            priorities[childNumber] = CWTPTimes[3];
            // int pid = CWTPTimes[4];
            
            childNumber++;
        }

        for (int i = 0; i < 30; i++)
        {
            printf(1,"*** childProcess CBT: %d, waiting time: %d,turn around time: %d, priority: %d ***\n",CBTs[i], waitingTimes[i],turnAroundTimes[i], priorities[i]);
        }

        printf(1, "\n\n\n =====> AVERAGE FOR EACH CLASS <=====\n\n");
        float averageCBTsPerClass[7] = {0};
        float averageWaitingTimesPerClass[7] = {0};
        float averageTurnAroundTimesPerClass[7] = {0};

        
        for (int i = 0; i < 30; i++)
        {
            averageCBTsPerClass[priorities[i]] += (float)(CBTs[i]/5);
            averageWaitingTimesPerClass[priorities[i]] += (float)(waitingTimes[i]/5);
            averageTurnAroundTimesPerClass[priorities[i]] += (float)(turnAroundTimes[i]/5);
        }
        
        for (int j = 1; j < 7; j++)
        {
            printf(1, "priority: %d, AVG of CBTs: %f, AVG of turnAround times: %f",
                 "AVG of waiting times: %f\n",
                j, averageCBTsPerClass[j], averageTurnAroundTimesPerClass[j], averageWaitingTimesPerClass[j]);
        }
        
        printf(1, "\n\n\n ====> AVERAGE FOR ALL CHILDREN <====\n\n");

        float AVGAllCBTs = 0;
        float AVGAllTurnAroundTimes = 0;
        float AVGALLWaitingTimes = 0;

        for (int i = 1; i < 7; i++)
        {
            AVGAllCBTs += (float)averageCBTsPerClass[i]/6;
            AVGALLWaitingTimes += (float)averageWaitingTimesPerClass[i]/6;
            AVGAllTurnAroundTimes += (float)averageTurnAroundTimesPerClass[i]/6;
        }
        printf(1,"*******************************************************************");

        printf(1, "AVG ALL CBTS : %f, AVG ALL TURN AROUND TIMES: %f, AVG ALL WAITING TIMES: %f",
                AVGAllCBTs, AVGAllTurnAroundTimes, AVGALLWaitingTimes);
    }
    //children go to else
    else{
        for (int i = 0; i < 10; i++)
            printf(1, "/%d/: /%d/ \n", childNumber,  i);
    }

    while (wait() != -1)
        ;

    return 0;
}