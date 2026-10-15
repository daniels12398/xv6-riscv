#include "kernel/types.h"
#include "user/user.h"

int
main(void)
{
  int pid1, pid2;

  pid1 = fork();
  if (pid1 == 0) {
    setpriority(0);

    for (volatile int i = 0; i < 50000000; i++)
      ;

    printf("Process with priority 0 finished\n");
    exit(0);
  }

  pid2 = fork();
  if (pid2 == 0) {
    setpriority(10);

    for (volatile int i = 0; i < 50000000; i++)
      ;

    printf("Process with priority 10 finished\n");
    exit(0);
  }

  wait(0);
  wait(0);

  printf("Aging test completed\n");
  exit(0);
}
