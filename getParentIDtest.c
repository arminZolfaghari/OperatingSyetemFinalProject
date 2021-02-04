#include "types.h"
#include "stat.h"
#include "user.h"

int main()
{
    int parentID;
    int procID;
    //child process
    if (fork() == 0)
    {
        procID = getpid();
        parentID = getParentID();
        printf(1, "*this is process %d \t and the parent ID is %d *\n", procID, parentID);

        //new child process
        if (fork() == 0)
        {
            procID = getpid();
            parentID = getParentID();
            printf(1, "*this is process %d \t and the parent ID is %d *\n", procID, parentID);
        }
        wait();
        
    }
    //parent process
    else{
        wait();
        procID = getpid();
        parentID = getParentID();
        printf(1, "*this is process %d \t and the parent ID is %d *\n", procID, parentID);
    }
    
    exit();
    return 0;
}