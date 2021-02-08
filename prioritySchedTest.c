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
    {   //CWTPtimes is array: [0]: CBT, [1]: waitingTimes, [2]: turnAroundTimes
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
            printf(1,"*** childProcess PID: %d, CBT: %d, waiting time: %d,turn around time: %d, priority: %d ***\n",getpid() ,CBTs[i], waitingTimes[i],turnAroundTimes[i], priorities[i]);
        }
        
        
    
    }
    //children go to else
    else{
        int childPID = getpid();
        for (int i = 0; i < 10; i++)
            printf(1, "/childNumber: %d, PID: %d/ : /%d/ \n", childNumber, childPID, i);
    }
    
    

}