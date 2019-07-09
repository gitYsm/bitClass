#include <opencv2/opencv.hpp>
#include <iostream>
#include <time.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <sys/ipc.h>

using namespace cv;
using namespace std;
#define SHMSIZE	1000 //int * 100
VideoWriter *shmaddr;
VideoWriter writer;
int *shmaddr2;
Size size;
void *shared_Mem = (void*)0;
void *shared_Mem2 = (void*)0;
int shmid;
//VideoWriter *shmaddr;


int shmid2;

void exePr(int sig)
{
    
}

int main()
{
    
    while(1){
        printf("lets sig\n");
        
        printf("lets sig2\n");
        pause();
        printf("lets sig3\n");
    }
    

    //signal(SIGUSR2, NULL);	//프로그램 죽었는지 확인 signal 
    //pause();
	

	return 0;
}

//g++ -o videoPr videoPr.cpp $(pkg-config opencv --libs --cflags)
