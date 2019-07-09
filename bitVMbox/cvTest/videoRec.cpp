#include <opencv2/opencv.hpp>
#include <iostream>
#include <time.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <pthread.h>

using namespace cv;
using namespace std;

char fileName[20] = "Output1.avi";
int cnt = 1;
VideoWriter writer;
VideoWriter writer2;
Size size;
double fps = 30.0;
//void *makeGlobalVar(void *data){
void makeGlobalVar(){
	char output[10] = "Output";
	char avi[5] = "avi";
	sprintf(fileName, "%s%d.%s", output, cnt, avi);

	printf("inFile: %s\n", fileName);
	//writer2.open(fileName, VideoWriter::fourcc('M', 'J', 'P', 'G'), fps, size, true);
}
int main()
{
	Mat img_color;
	clock_t start, end;
	pid_t pid;
    double result;
	int fResult;
	int ret;

	//pthread_t p_thread[1];
	//비디오 캡쳐 초기화
	VideoCapture cap("res.avi");
	if (!cap.isOpened()) {
		cerr << "에러 - 카메라를 열 수 없습니다.\n";
		return -1;
	}
	int err;
	int status;
	// 동영상 파일을 저장하기 위한 준비  
	size = Size((int)cap.get(CAP_PROP_FRAME_WIDTH),
		(int)cap.get(CAP_PROP_FRAME_HEIGHT));

	
	
	if((pid=vfork())==0)	//자식 프로세스1 라이터, 폴더 용량검사 미리 열어놓기
    {
        //ret = execlp("./printP", "printP", NULL);	
		//폴더 용량검사와 writer공유 메모리에 저장 하는 프로그램
		
		//signal(SIGUSR1, makeGlobalVar);
		ret = execlp("./videoPr", "videoPr", NULL);
        //printf("pid=%ld, getpid=%ld, getppid=%ld \n",(long)pid, (long)getpid(), (long)getppid());
    }
    else{	//부모 프로세스 비디오 녹화수행.
		int a =1;
		
		writer.open("output.avi", VideoWriter::fourcc('M', 'J', 'P', 'G'), fps, size, true);
		
		if (!writer.isOpened())
		{
			cout << "동영상을 저장하기 위한 초기화 작업 중 에러 발생" << endl;
			return 1;
		}
		//(*shmaddr) = writer;
		start = time(NULL);
		double globalT = 0;
		
		char output[10] = "Output";
		
		char avi[5] = "avi";
		//makeGlobalVar();
		// if((err = pthread_create(&p_thread[0], NULL, makeGlobalVar, (void*)&a)) < 0){
		// 	perror("thread create erro : ");
		// 	exit(1);
		// }
		
		while(1)
		{
			int version = 0;
			Mat test;
			//cap.read(img_color);
			cap >> test;
			if (test.empty()) {
				cerr << "빈 영상이 캡쳐되었습니다.\n";
				break;
			}
			//동영상 파일에 한 프레임을 저장함.  
			// writer.write(img_color);
			// imshow("Color", img_color);
			//cvtColor(test, img_color, COLOR_BGR2GRAY);
			writer.write(test);
			imshow("Color", test);
			
			if (waitKey(7) == 27)
				break;
			
			end = time(NULL); // 시간 측정 끝
			result = (double)(end - start);
			//printf("%f\n", result); //결과 출력
			//change writer.
			
			
			if( result  == (double)5*cnt && globalT != (double)5*cnt){
				//pthread_join(p_thread[0], (void**)&status);
				//writer = writer2;
				//makeGlobalVar();
				// if((err = pthread_create(&p_thread[0], NULL, makeGlobalVar, (void*)&a)) < 0){
				// 	perror("thread create erro : ");
				// 	exit(1);
				// }
				//printf("%f\n", result); //결과 출력
				sprintf(fileName, "%s%d.%s", output, cnt, avi);
				//printf("fileName:%s",fileName);
				writer.open(fileName, VideoWriter::fourcc('M', 'J', 'P', 'G'), fps, size, true);
    			//writer.write(test);
				globalT = 3*cnt;
				cnt++;
				     //create thread2
				printf("cnt: %d\n", cnt);
				
				//printf("thread join : %d, %s\n", status, fileName);
			
			}
			
		}
		//pthread_join(p_thread[0], (void**)&status);
		//signal(SIGUSR1, NULL);	//프로그램 죽었는지 확인 signal 
		//pause();
    }
	
	return 0;
}

//g++ -o videoRec videoRec.cpp $(pkg-config opencv --libs --cflags)
