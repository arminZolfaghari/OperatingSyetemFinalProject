#include "syscall.h"
#include "traps.h"

#define SYSCALL(name) \
  .globl name; \
  name: \
    movl $SYS_ ## name, %eax; \
    int $T_SYSCALL; \
    ret

SYSCALL(fork)
SYSCALL(exit)
SYSCALL(wait)
SYSCALL(pipe)
SYSCALL(read)
SYSCALL(write)
SYSCALL(close)
SYSCALL(kill)
SYSCALL(exec)
SYSCALL(open)
SYSCALL(mknod)
SYSCALL(unlink)
SYSCALL(fstat)
SYSCALL(link)
SYSCALL(mkdir)
SYSCALL(chdir)
SYSCALL(dup)
SYSCALL(getpid)
SYSCALL(sbrk)
SYSCALL(sleep)
SYSCALL(uptime)
SYSCALL(testGetYear)
SYSCALL(getParentID)
SYSCALL(getSyscallCounter)
SYSCALL(getChildren)
SYSCALL(setQuantum)
SYSCALL(setPriority)
SYSCALL(changePolicy)
SYSCALL(getCBT)
SYSCALL(getTurnAroundTime)
SYSCALL(getWaitingTime)
SYSCALL(getTotalCBT)
SYSCALL(getTotaltat)
SYSCALL(getTotalwt)
SYSCALL(waitForPrioritySchedule)
SYSCALL(setLayer)
SYSCALL(waitForMultiLayerSchedule)
