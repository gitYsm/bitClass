#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <stdlib.h>

int main( void)
{
    printf("ppid: %ld", (long)getppid());
    int i = 0;
    while(1){
        printf("i'm alilve\n");
        sleep(1);
        kill((long)getppid(),SIGUSR1);
        if( i == 5){
            exit(0);
        }
        i++;
    }
}