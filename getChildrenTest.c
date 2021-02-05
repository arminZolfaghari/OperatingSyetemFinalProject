#include "types.h"
#include "stat.h"
#include "user.h"
#include "param.h"
// #include "string.h"


int main()
{
    int parentID = getpid();
    int *children = malloc(NPROC);
    char result[1024] = "this process is ";
    

    //create process
    fork();
    fork();
    fork();

    int numberOfChildren = getChildren(children);

    if (getpid() == parentID)
    {
        printf(1, "%s", result);
        printf(1, "%d", parentID);
        printf(1, " and children are");
        // char parentIDChar[100];
        // sprintf(parentIDChar, "%d", parentID);
        // strcat(result, parentIDChar);

        for (int i = 0; i < numberOfChildren - 1; i++)
            {
                int childID = children[i];
                printf(1, " %d,", childID);
                // char childIDChar[100];
                // sprintf(childIDChar, "%d", childID);
                // strcat(result, childIDChar);
                // strcat(result, ",");
            }
        int childID = children[numberOfChildren - 1];
        printf(1, " %d.", childID);
        // char childIDChar[100];
        // sprintf(childIDChar, "%d", childID);
        // strcat(result, childIDChar);
        printf(1, "\n**number of children : %d**", numberOfChildren);
    }
    while(wait() != -1);
    exit();
    return 0; 
}
    


//     //child process
//     if (fork() == 0)
//     {
//         /* code */
//     }
//     //parent process
//     else{
//         if (fork() == 0)
//         {
//             /* code */
//         }
//         else{
//             if (fork() == 0)
//             {
//                 /* code */
//             }
//             else{
//                 parentID = getpid();
//                 printf(1, "%s", result);
//                 printf(1, "%d", parentID);
//                 // char parentIDChar[100];
//                 // sprintf(parentIDChar, "%d", parentID);
//                 // strcat(result, parentIDChar);

                
//                 for (int i = 0; i < numberOfChildren; i++)
//                 {
//                     int childID = *(children + i);
//                     printf(1, " %d,", childID);
//                     // char childIDChar[100];
//                     // sprintf(childIDChar, "%d", childID);
//                     // strcat(result, childIDChar);
//                     // strcat(result, ",");
//                 }
//                 int childID = *(children + numberOfChildren);
//                     printf(1, " %d.", childID);
//                     // char childIDChar[100];
//                     // sprintf(childIDChar, "%d", childID);
//                     // strcat(result, childIDChar);
//             }
//             wait();
//         }
        
//     }
    

//     exit();
//     return 0;
// }