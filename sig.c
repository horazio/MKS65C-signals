#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

static void sighandler(int signo){
  if(signo == SIGINT){
    int fd = open("log.txt", O_APPEND | O_WRONLY);
    if(fd == -1){
      printf("\nWhoops: %s\n", strerror(errno));
    }

    char message[33] = "The program exited due to SIGINT\n";
    write(fd, message, 33);

    close(fd);

    exit(0);
  }
  if(signo == SIGUSR1){
    printf("\nThe PID of my parent is: %d\n", getppid());
  }
}

int main(){
  signal(SIGUSR1, sighandler);
  signal(SIGINT, sighandler);
  
  while (1){
    printf("Hello I'm : %d\n", getpid());
    sleep(1);
  }
  return 0;
}
