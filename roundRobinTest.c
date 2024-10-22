#include "types.h"
#include "stat.h"
#include "user.h"

int main()
{
    printf(1, "/%d/\n\n", changePolicy(1));

    int father = getpid();
    for (int i = 0; i < 10; i++)
    {
        if (fork() > 0)
            break;
    }

    if (father != getpid())
    {
        wait();
        for (int i = 0; i < 200; i++){
            printf(1, "/%d/: %d\n", getpid(), i);
            wait();
        }
        
        int turnAroundTime = getTurnAroundTime(getpid());
        int waitingTime = getWaitingTime(getpid());
        int CBT = getCBT(getpid());

        wait();

        printf(1, "\nTurn Around Time for process /%d/ :%d\n", getpid(), turnAroundTime);
        printf(1, "Waiting Time for process /%d/ :%d\n", getpid(), waitingTime);
        printf(1, "CBT for process /%d/ :%d\n\n\n", getpid(), CBT);
    } 
    else {
        wait();
        printf(1, "Total Turn Around Time : %d\n", getTotaltat(getpid()));
        printf(1, "Total Waiting Time : %d\n", getTotalwt(getpid()));
        printf(1, "Total CBT : %d\n\n\n", getTotalCBT(getpid()));

        printf(1, "Average Turn Around Time : %d\n", getTotaltat(getpid())/10);
        printf(1, "Average Waiting Time : %d\n", getTotalwt(getpid())/10);
        printf(1, "Average CBT : %d\n\n\n", getTotalCBT(getpid())/10);
    }

    while (wait() != -1)
    {
        ;
    }

    exit();
}