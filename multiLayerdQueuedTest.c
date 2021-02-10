#include "types.h"
#include "stat.h"
#include "user.h"

int main()
{
    printf(1, "\n Policy: /%d/\n\n", changePolicy(3));

    // int childNums = 40;
    int childNumber = 0;

    int father = getpid();
    for (int i = 0; i < 40; i++)
    {
        if (fork() > 0)
            break;

        if (i >= 0 && i < 10) {
            setLayer(1);
        }
        else if (i >= 10 && i < 20){
            setLayer(2);
            setPriority(i%6);
        }
        else if (i >= 20 && i < 30){
            setLayer(3);
            setPriority(i%6);
        }
        else if (i >= 30 && i < 40){
            setLayer(4);
        }

        // childNumber = i + 1;
    }

    if (father != getpid())
    {
        
        for (int i = 0; i < 200; i++){
            printf(1, "/%d/: /%d/\n", childNumber, i);
            
        }

    } 
    else {
        int CBTs[40] = {0};
        int waitingTimes[40] = {0};
        int turnAroundTimes[40] = {0};
        int queue[40] = {0};
        int priorities[40] = {0};

        int *CWTQTimes = malloc(5 * sizeof(int));
        childNumber = 0;

        while (waitForMultiLayerSchedule(CWTQTimes) > 0)
        {
            CBTs[childNumber] = CWTQTimes[0];
            waitingTimes[childNumber] = CWTQTimes[1];
            turnAroundTimes[childNumber] = CWTQTimes[2];
            queue[childNumber] = CWTQTimes[3];
            priorities[childNumber] = CWTQTimes[4];
            // int pid = CWTPTimes[4];
            
            childNumber++;
        }

        for (int i = 0; i < 40; i++)
        {
            printf(1,"*** childProcess CBT: %d, waiting time: %d,turn around time: %d, priority: %d , queue: %d***\n",CBTs[i], waitingTimes[i],turnAroundTimes[i], priorities[i], queue[i]);
        }



        printf(1, "\n\n\n =====> AVERAGE FOR EACH layer <=====\n\n");
        float averageCBTsPerLayer[5] = {0};
        float averageWaitingTimesPerLayer[5] = {0};
        float averageTurnAroundTimesPerLayer[5] = {0};

        
        for (int i = 0; i < 40; i++)
        {
            averageCBTsPerLayer[queue[i]] += (float)(CBTs[i]/10);
            averageWaitingTimesPerLayer[queue[i]] += (float)(waitingTimes[i]/10);
            averageTurnAroundTimesPerLayer[queue[i]] += (float)(turnAroundTimes[i]/10);
        }
        
        for (int j = 1; j < 5; j++)
        {
            printf(1, "priority: %d, AVG of CBTs: %d, AVG of turnAround times: %d , AVG of waiting times: %d\n",
                j, (int)averageCBTsPerLayer[j], (int)averageTurnAroundTimesPerLayer[j], (int)averageWaitingTimesPerLayer[j]);
        }

        printf(1, "\n\n\n ====> AVERAGE FOR ALL CHILDREN <====\n\n");

        float AVGAllCBTs = 0;
        float AVGAllTurnAroundTimes = 0;
        float AVGALLWaitingTimes = 0;

        for (int i = 1; i < 5; i++)
        {
            AVGAllCBTs += (float)averageCBTsPerLayer[i]/4;
            AVGALLWaitingTimes += (float)averageWaitingTimesPerLayer[i]/4;
            AVGAllTurnAroundTimes += (float)averageTurnAroundTimesPerLayer[i]/4;
        }
        printf(1,"*******************************************************************\n");

        printf(1, "AVG ALL CBTS : %d, AVG ALL TURN AROUND TIMES: %d, AVG ALL WAITING TIMES: %d\n\n", (int)AVGAllCBTs, (int)AVGAllTurnAroundTimes, (int)AVGALLWaitingTimes);


    }

    while (wait() != -1)
    {
        ;
    }

    exit();
}