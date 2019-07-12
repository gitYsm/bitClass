#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <wait.h> // wait()
#include <sys/types.h>
#include <time.h>

pid_t pid;
clock_t start, end;
double result;
void sigHandler(int sig)
{
    printf("killTest : I got signal %d i'm still alive\n",sig);
    start = time(NULL); // 시간 측정 끝
    //(void)signal(SIGINT,SIG_DFL);
}
void execPrintP(){
    int x=0;
    int status;
    int ret;
    int test = 100;
    if((pid=fork())==0)
    {
        ret = execlp("./printP", "printP", NULL);
        printf("pid=%ld, getpid=%ld, getppid=%ld \n",(long)pid, (long)getpid(), (long)getppid());
        
    }
    else{
        printf("pid=%ld, I am process %ld\n",(long)pid, (long)getpid());
        signal(SIGUSR1, sigHandler);
        pause();
    }
}
int main(void){

    int x=0;
    int status;
    int ret;

    //ret = execl("~/bitClass/bitVMbox/linuxSys2/forkEx", "~/bitClass/bitVMbox/linuxSys2/forkEx", NULL);
    //printf("retttttt: %d",ret);
    start = time(NULL); // 시간 측정 끝
    execPrintP();
    while(1){
        end = time(NULL); // 시간 측정 끝
        result = (double)(end - start);
        if(result > 1){
            printf("signal error, restart!");
            kill(pid, SIGKILL);
            execPrintP();
        }
        sleep(1);
    }
    
    return 0;
}