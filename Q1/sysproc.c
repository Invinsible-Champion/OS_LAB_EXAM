#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"
int sys_fork(void)
{
  return fork();
}

int sys_exit(void)
{
  exit();
  return 0; // not reached
}

int sys_wait(void)
{
  return wait();
}

int sys_kill(void)
{
  int pid;

  if (argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

int sys_getpid(void)
{
  return myproc()->pid;
}

int sys_sbrk(void)
{
  int addr;
  int n;

  if (argint(0, &n) < 0)
    return -1;
  addr = myproc()->sz;
  if (growproc(n) < 0)
    return -1;
  return addr;
}

int sys_sleep(void)
{
  int n;
  uint ticks0;

  if (argint(0, &n) < 0)
    return -1;
  acquire(&tickslock);
  ticks0 = ticks;
  while (ticks - ticks0 < n)
  {
    if (myproc()->killed)
    {
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
int sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}

// for priority_scheduling
int
sys_set_priority(void)
{
  int pid, priority;

  if(argint(0, &pid) < 0)
    return -1;

  if(argint(1, &priority) < 0)
    return -1;

  return set_priority(pid, priority);
}
// for q1

int sys_mprotect(void)
{
  int addr, len;
  struct proc *p = myproc();

  if (argint(0, &addr) < 0 || argint(1, &len) < 0)
    return -1;

  if (addr % PGSIZE != 0 || len <= 0)
    return -1;

  if ((uint)addr > p->sz)
    return -1;

  if ((uint)len > (p->sz - (uint)addr) / PGSIZE)
    return -1;

  if (change_perm(p->pgdir, (uint)addr, len, 0) < 0)
    return -1;

  lcr3(V2P(p->pgdir));

  return 0;
}

int
sys_munprotect(void)
{
  int addr, len;
  struct proc *p = myproc();

  if(argint(0, &addr) < 0 || argint(1, &len) < 0)
    return -1;

  if(addr % PGSIZE != 0 || len <= 0)
    return -1;

  if((uint)addr > p->sz)
    return -1;

  if((uint)len > (p->sz - (uint)addr) / PGSIZE)
    return -1;

  if(change_perm(p->pgdir, (uint)addr, len, 1) < 0)
    return -1;

  lcr3(V2P(p->pgdir));

  return 0;
}