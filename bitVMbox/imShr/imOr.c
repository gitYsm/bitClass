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

	printf("Memory attached at %p\n", (char*)shared_Mem);
	shmaddr = (char*)shared_Mem;
    shmaddr2 = (int*)shared_Mem2;

    if ( 0 < ( fd = open( "../bitAna/data/1.jpg", O_RDONLY)))
    {
        while( 0 < ( len = read( fd, buff, SHMSIZE)))   //  4 byte씩 읽씁니다.
        {
            memcpy(shmaddr, buff, sizeof(buff));
            *(shmaddr2)=len;

            printf("*(shmaddr2)=%d\n",*(shmaddr2));
            printf("len=%d\n",len);
            //sleep(1);
            while(*(shmaddr2)!=0);
            //printf("shmaddr:%X, data:%d\n", shmaddr + i, *(shmaddr + i));
        }
        close( fd);
    }
    else
    {
        printf( "파일 열기에 실패했습니다.\n");
    }

    *(shmaddr2)= -1;
	// step4. shmdt
	if (shmdt(shared_Mem) == -1 || shmdt(shared_Mem2) == -1)
	{
		fprintf(stderr, "shmdt failed\n");
		exit(EXIT_FAILURE);
	}
	
	
	exit(EXIT_SUCCESS);
}