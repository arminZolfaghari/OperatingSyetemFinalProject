#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"

int
sys_fork(void)
{
  return fork();
}

int
sys_exit(void)
{
  exit();
  return 0;  // not reached
}

int
sys_wait(void)
{
  return wait();
}

int
sys_kill(void)
{
  int pid;

  if(argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

int
sys_getpid(void)
{
  return myproc()->pid;
}

int
sys_sbrk(void)
{
  int addr;
  int n;

  if(argint(0, &n) < 0)
    return -1;
  addr = myproc()->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

int
sys_sleep(void)
{
  int n;
  uint ticks0;

  if(argint(0, &n) < 0)
    return -1;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(myproc()->killed){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

// return how many clock tick interrupts have occurred
// since start.
int
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}

int sys_testGetYear(void)
{
  return testGetYear();
}

int sys_getParentID(void)
{
  return getParentID();
}

int sys_getChildren(void)
{
  int* childrenPIDAddress;
  if(argptr(0, (void *) &childrenPIDAddress, sizeof(*childrenPIDAddress)) == -1)
    return -1;
  else{
    return getChildren(childrenPIDAddress);
  }
}


// extern int syscallNums;
// extern int (*syscalls[26])(void);
// extern int systemcallNos;
int syscallNums = 25;

int sys_getSyscallCounter(void)
{
  int systemcallNumber;

  if(argint(0, &systemcallNumber) > syscallNums || (systemcallNumber < 0)) {
  // if(argint(0, &systemcallNumber) > syscallNums || (systemcallNumber < 0) || !(syscalls[systemcallNumber])) {
  // if(argint(0, &systemcallNumber) > systemcallNos || (systemcallNumber < 0) ) {
    return -1;
  }
  return getSyscallCounter(systemcallNumber);
}


int sys_setQuantum(void)
{
  int inputQuantom;

  if(argint(0, &inputQuantom) < 0) {
    return -1;
  }
  setQuantum(inputQuantom);
  return 0;
}


int sys_setPriority(void)
{
  int newPriority;
  if (argint(0, &newPriority) < 0){}
  {
    return -1;
  }
  return setPriority(newPriority);
}


int sys_changePolicy(void)
{
  int newPolicy;
  if (argint(0, &newPolicy) < 0)//{}
  {
    return -1;
  }
  return changePolicy(newPolicy);
}

int sys_getCBT(void)
{
  int pid;

  if (argint(0, &pid) < 0)
  {
    return -1;
  }
  return getCBT(pid);
}

int sys_getTurnAroundTime(void)
{
  int pid;
  if (argint(0, &pid) < 0)
  {
    return -1;
  }
  return getTurnAroundTime(pid);
}

int sys_getWaitingTime(void)
{
  int pid;
  if (argint(0, &pid) < 0)
  {
    return -1;
  }
  return getWaitingTime(pid);
}