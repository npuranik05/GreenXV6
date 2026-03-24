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

int
sys_update_env(void)
{
  int zone, delta;
  if(argint(0, &zone) < 0 || argint(1, &delta) < 0) return -1;
  return update_env_var(zone, delta);
}

int sys_get_env(void) {
  int zone;
  if(argint(0, &zone) < 0) return -1;
  return get_env_var(zone);
}

int sys_get_energy(void) {
  int pid;
  if(argint(0, &pid) < 0) return -1;
  return get_proc_energy(pid);
}

int sys_set_zone(void) {
  int zone, mitigator;
  if(argint(0, &zone) < 0 || argint(1, &mitigator) < 0) return -1;
  myproc()->zone_affiliation = zone;
  myproc()->is_mitigator = mitigator;
  return 0;
}
