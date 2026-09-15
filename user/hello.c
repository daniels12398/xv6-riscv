#include "kernel/types.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
  if (argc == 2) {
    printf("Hello, %s!\n", argv[1]);
  } else {
    printf("Hello, World!\n");
  }

  exit(0);
}
