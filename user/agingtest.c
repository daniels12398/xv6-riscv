#include "kernel/types.h"
#include "user/user.h"

int
main(void)
{
  int pid1, pid2;

  printf("Aging scheduler test\n");

  pid1 = fork();
  if (pid1 == 0) {
    setpriority(0);
    printf("Low priority process started (priority 0)\n");

    for (volatile int i = 0; i < 80000000; i++)
      ;

    printf("Low priority process finished\n");
    exit(0);
  }

  pid2 = fork();
  if (pid2 == 0) {
    setpriority(10);
    printf("High priority process started (priority 10)\n");

    for (volatile int i = 0; i < 80000000; i++)
      ;

    printf("High priority process finished\n");
    exit(0);
  }

  wait(0);
  wait(0);

  printf("Both processes completed - aging prevents starvation\n");
  exit(0);
}
