#include "kernel/types.h"
#include "user/user.h"

int main(int argc, char *argv[]) {
  int p1[2], p2[2];

  char buf[]={'a'};
  pipe(p1);pipe(p2);
  int ret = fork();
          if(ret==0){	
                int pid = getpid();
                close(p1[0]);
                close(p2[1]);
                read(p1[1],buf,1);
                printf("%d: received ping\n",pid);
                write(p2[0],buf,1);
               	exit(0);
        }
        else{
                int pid = getpid();
                close(p2[0]);
                close(p1[1]);
                read(p2[1],buf,1);
                printf("%d: received pong\n",pid);
                write(p1[0],buf,1);
                exit(0);
        }
}
