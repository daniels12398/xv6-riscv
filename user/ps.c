#include "kernel/param.h"
#include "kernel/types.h"
#include "kernel/pstat.h"
#include "user/user.h"

int
main(int argc, char **argv)
{
  struct pstat uproc[NPROC];
  int nprocs;
  int i;
  uint age;
  char *state;
  static char *states[] = {
    [SLEEPING]  "sleeping",
    [RUNNABLE]  "runnable",
    [RUNNING]   "running ",
    [ZOMBIE]    "zombie  "
  };

  nprocs = getprocs(uproc);
  if (nprocs < 0)
    exit(-1);

  printf("pid state size ppid priority age name\n");
  for (i=0; i<nprocs; i++) {
    state = states[uproc[i].state];
   if (uproc[i].state == RUNNABLE)
   age = uptime() - uproc[i].readytime;
   else
  age = 0;
    printf("%d %s %ld %d %d %d %s\n", uproc[i].pid, state,
       uproc[i].size, uproc[i].ppid,
       uproc[i].priority, age, uproc[i].name);
}
  exit(0);
}
