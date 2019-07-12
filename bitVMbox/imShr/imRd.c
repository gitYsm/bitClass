#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h> 
//For IPC 
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>

#define SHMSIZE	1024 //int * 100

int main(void)
{
	void *shared_Mem = (void*)0;
	int shmid;
	int *shmaddr;
    void *shared_Mem2 = (void*)0;
	int shmid2;
	int *shmaddr2;
    int rdData;
	int i;
    char     buff[SHMSIZE];
    int      fd;
    int len;
	// step0. ftok()

	// step1. shmget
	shmid = shmget((key_t)100, sizeof(char)*SHMSIZE, 0666 | IPC_CREAT);
    shmid2 = shmget((key_t)101, sizeof(int)*2, 0666 | IPC_CREAT);
	if (shmid == -1)
	{
		fprintf(stderr, "shmget failed\n");
		exit(EXIT_FAILURE);
	}

	// step2. shmat
	shared_Mem = shmat(shmid, (void*)0, 0);
    shared_Mem2 = shmat(shmid2, (void*)0, 0);
	if (shared_Mem == (void*)-1)
	{
		fprintf(stderr, "shmat failed\n");
		exit(EXIT_FAILURE);
	}

	printf("Memory attached at %X\n", (int)shared_Mem);
	shmaddr = (int*)shared_Mem;
    shmaddr2 = (int*)shared_Mem2;

    fd = open("lena_copy.jpg", O_WRONLY | O_CREAT | O_TRUNC);
	printf("flag1=%d\n", *(shmaddr2));
	while(*(shmaddr2)!=-1)
	{
		len = *(shmaddr2);
		memcpy(buff,shmaddr,len);
		*(shmaddr2)=0;
		write(fd,buff,len);
		printf("flag2=%d\n",*(shmaddr2));
		//sleep(1);
	}

	// step4. shmdt
	if (shmdt(shared_Mem) == -1 || shmdt(shared_Mem2) == -1)
	{
		fprintf(stderr, "shmdt failed\n");
		exit(EXIT_FAILURE);
	}
	// step 5.2 shmctl : IPC_RMID
	if (shmctl(shmid, IPC_RMID, 0) == -1 || shmctl(shmid2, IPC_RMID, 0) == -1)
	{
			fprintf(stderr, "shmctl (IPC_RMID) failed\n");
			exit(EXIT_FAILURE);
	}
	
	exit(EXIT_SUCCESS);
}