#include "types.h"
#include "stat.h"
#include "user.h"
#include "param.h"

int main()
{
    int originalParentID = getpid();
    int childNumber;

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

    //this loop for children process
    if (originalParentID != getpid())
    {
        int childPID = getpid();
        for (int i = 0; i < 250; i++)
            printf(1, "/childNumber: %d, PID: %d/ : /%d/ \n", childNumber, childPID, i);

        int turnAroundTime =    
        

    }
    
    

}