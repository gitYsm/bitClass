#include <signal.h>
#include <stdio.h>
#include <unistd.h>

// SIGINT에 대응하는 핸들러
void sigHandler(int sig)
{
    printf("OUCH! - I got signal %d\n", sig);
    (void) signal(SIGINT, SIG_DFL);
}
// main함수
int main()
{
    signal(SIGINT, sigHandler) == SIG_ERR;

    for(;;){
        printf("1");
        pause();
    }
    
    while(1) {
    printf("Hello World!\n");
    sleep(1);
    }
}