#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <ctype.h>
#include <errno.h>
#include <sys/param.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/stat.h>

int main () {
  int pid = getpid();
  int page, frame;
  printf("PID %d\n",pid);

  page = getchar();
  frame = get
  
  return 0;
}