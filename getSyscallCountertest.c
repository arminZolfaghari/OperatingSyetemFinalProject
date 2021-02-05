#include "types.h"
#include "stat.h"
#include "user.h"

int main(){
    int systemcallCounter;
    int procID;
    //child process
    if (fork() == 0)
    {
        procID = getpid();
        systemcallCounter = getSyscallCounter(1);
        printf(1, "*this is process %d \t and Syscall Counter 1 is %d *\n", procID, systemcallCounter);

        //new child process
        if (fork() == 0)
        {
            procID = getpid();
            systemcallCounter = getSyscallCounter(1);
            printf(1, "*this is process %d \t and Syscall Counter 1 is %d *\n", procID, systemcallCounter);
        } else {
            wait();
            procID = getpid();
            systemcallCounter = getSyscallCounter(1);
            printf(1, "*this is process %d \t and Syscall Counter 1 is %d *\n", procID, systemcallCounter);
        }
        wait();
        
    }
    //parent process
    else{
        wait();
        procID = getpid();
        systemcallCounter = getSyscallCounter(1);
        printf(1, "*this is process %d \t and Syscall Counter 1 is %d *\n", procID, systemcallCounter);
    }
    
    exit();
    return 0;
}