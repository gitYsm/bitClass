#include <stdio.h> // printf()
#include <unistd.h> // fork()
#include <sys/types.h> // pid_t
#include <wait.h> // wait()
#include <sys/wait.h>
#include <stdlib.h>
#include <sys/types.h> wait()and waitpid()
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

void pr_exit(int status){
if (WIFEXITED(status))
    printf("normal termination, exit status = %d\n",
    WEXITSTATUS(status));
else if (WIFSIGNALED(status))
    printf("abnormal termination, signal number = %d%s\n",
    WTERMSIG(status),
    WCOREDUMP(status) ? "(core file generated)" : "");
else if (WIFSTOPPED(status))
    printf("child stopped, signal number = %d\n",
    WSTOPSIG(status));}

int main(void){
    pid_t pid; int status;
    if ( (pid = fork()) < 0)
        perror("fork error");
    else if (pid == 0) exit(7); /* child */

    if (wait(&status) == pid) /* wait for child */
        pr_exit(status); /* and print its status */
    if ( (pid = fork()) < 0)
        perror("fork error");
    else if (pid == 0) abort(); /* child : generates SIGABRT */

    if (wait(&status) == pid) /* wait for child */
        pr_exit(status); /* and print its status */
    if ( (pid = fork()) < 0)
        perror("fork error");
    else if (pid == 0) status /= 0; /* child: divide by 0 generates SIGFPE */
    if (wait(&status) == pid) /* wait for child */
        pr_exit(status); /* and print its status */
}