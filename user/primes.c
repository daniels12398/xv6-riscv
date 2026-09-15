#include "kernel/types.h"
#include "user/user.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Winfinite-recursion"

void
primes(int in_fd)
{
  int p;

  if (read(in_fd, &p, sizeof(p)) == 0) {
    close(in_fd);
    exit(0);
  }

  printf("prime %d\n", p);

  int fds[2];
  pipe(fds);

  if (fork() == 0) {
    // Child: becomes the next stage of the pipeline.
    // It reads from the new pipe.
    close(fds[1]);
    close(in_fd);

    primes(fds[0]);

  } else {
    // Parent: filters numbers and writes them to the next stage.
    close(fds[0]);

    int n;
    while (read(in_fd, &n, sizeof(n)) > 0) {
      if (n % p != 0) {
        write(fds[1], &n, sizeof(n));
      }
    }

    close(in_fd);
    close(fds[1]);
    wait(0);
    exit(0);
  }
}

#pragma GCC diagnostic pop

int
main(void)
{
  int fds[2];
  pipe(fds);

  if (fork() == 0) {
    // Child: first stage of the pipeline.
    close(fds[1]);
    primes(fds[0]);

  } else {
    // Parent: feeds numbers 2 through 35.
    close(fds[0]);

    for (int i = 2; i <= 35; i++) {
      write(fds[1], &i, sizeof(i));
    }

    close(fds[1]);
    wait(0);
  }

  exit(0);
}
