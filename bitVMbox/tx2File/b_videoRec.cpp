#include <opencv2/opencv.hpp>
#include <iostream>
#include <time.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <pthread.h>

using namespace cv;
using namespace std;
pid_t pid;

void killAll(int sig){
    kill(pid, SIGKILL);
    (void)signal(SIGINT,SIG_DFL);
    kill(getpid(), SIGINT);
}

void mkFork(int sig){
    printf("죽은 자식 살리기");
    fflush;
    if((pid=fork())==0)	//자식 프로세스1 라이터, 폴더 용량검사 미리 열어놓기
    {
		int ret;
        //실행시 용량 검사와 저장 폴더 확인 및 생성
		ret = execlp("./manageFolder", "manageFolder", NULL);
    }
}

int main()
{
	
	int status;
	if((pid=fork())==0)	//자식 프로세스1 라이터, 폴더 용량검사 미리 열어놓기
    {
		int ret;
        //실행시 용량 검사와 저장 폴더 확인 및 생성
		ret = execlp("./manageFolder", "manageFolder", NULL);
    }
    else{	//부모 프로세스 비디오 녹화수행.
		signal(SIGINT, killAll);
        signal(SIGCHLD, mkFork);
		Mat img_color;
		double fps = 30.0;
		VideoWriter writer;
		clock_t start, end;
		double result;
		struct tm *t;
		char dir[30] = "/home/yang/bitClass/bRec";
		char fileName[50];
		char fileDir[100];
		strcpy(fileDir, dir);
		char imgString[100];

		//녹화길이 설정
		int recTerm = 60;
		int cnt = 1;
		double globalT = 0;
		
		//비디오 캡쳐 초기화
		//VideoCapture cap("nvarguscamerasrc ! video/x-raw(memory:NVMM), width=(int)640, height=(int)480,format=(string)NV12, framerate=(fraction)30/1 ! nvvidconv flip-method=0 ! video/x-raw, format=(string)BGRx ! videoconvert ! video/x-raw, format=(string)BGR ! appsink");
        VideoCapture cap("../cvTest/rec.mp4");
		if (!cap.isOpened()) {
			cerr << "에러 - 카메라를 열 수 없습니다.\n";
			exit(0);
		}
				
		// 동영상 파일을 저장하기 위한 준비  
		Size size = Size((int)cap.get(CAP_PROP_FRAME_WIDTH),
			(int)cap.get(CAP_PROP_FRAME_HEIGHT));
		
		start = time(NULL);
		t = localtime(&start);
		sprintf(fileName,"/%d%.2d%.2d_%.2d/%d-%.2d-%.2d_%.2d:%.2d:%.2d.avi"
			,t->tm_year + 1900,(t->tm_mon + 1),t->tm_mday, t->tm_hour
			,t->tm_year + 1900,(t->tm_mon + 1),t->tm_mday, t->tm_hour, t->tm_min, t->tm_sec);
		strcat(fileDir, fileName);
		//59분일 경로 생성 sig 줌
		if(t->tm_min == 59){
			kill(pid, SIGUSR1);
		}
		printf("first file:: %s\n\n", fileDir);
		writer.open(fileDir, VideoWriter::fourcc('D', 'I', 'V', 'X'), fps, size, true);
		if (!writer.isOpened())
		{
			cout << "동영상을 저장하기 위한 초기화 작업 중 에러 발생" << endl;
			exit(0);
		}
		
	
		//Mat img6(480, 640, CV_8UC3, Scalar(0,0,0));
		while(1)
		{
			int version = 0;
			//cap.read(img_color);
			cap >> img_color;
			if (img_color.empty()) {
				cerr << "빈 영상이 캡쳐되었습니다.\n";
				break;
			}

			end = time(NULL); // 시간 측정 끝
			
            //frame에 시간 넣기
            // center the text
			//Point textOrg((test.cols - size.width)/2,(test.rows + size.height)/2);
			Point textOrg(10, (size.height) - 10);

			t = localtime(&end);
			sprintf(imgString,"%d-%.2d-%.2d %.2d:%.2d:%.2d",t->tm_year + 1900,(t->tm_mon + 1),t->tm_mday, t->tm_hour, t->tm_min, t->tm_sec);
			int thickness = 2;
			putText(img_color, imgString, textOrg, FONT_HERSHEY_PLAIN, 2, Scalar::all(255), thickness, 8);
	
			if (img_color.empty()) {
				cerr << "2빈 영상이 캡쳐되었습니다.\n";
				break;
			}
			
			imshow("Color", img_color);
			writer.write(img_color);

			if (waitKey(20) == 27)
				break;
			
			result = (double)(end - start);
            //녹화본 한개 시간 됐는지 확인.
			if( result  == (double)recTerm*cnt && globalT != (double)recTerm*cnt){
                //경로 생성
				if(t->tm_min == 59){
					kill(pid, SIGUSR1);
				}
                //파일이름 만들기
				strcpy(fileDir, dir);
				sprintf(fileName,"/%d%.2d%.2d_%.2d/%d-%.2d-%.2d_%.2d:%.2d:%.2d.avi"
			,t->tm_year + 1900,(t->tm_mon + 1),t->tm_mday, t->tm_hour
			,t->tm_year + 1900,(t->tm_mon + 1),t->tm_mday, t->tm_hour, t->tm_min, t->tm_sec);
				strcat(fileDir, fileName);
				printf("new file!!!! %s\n",fileDir);
				fflush;
				writer.open(fileDir, VideoWriter::fourcc('D', 'I', 'V', 'X'), fps, size, true);	
				
                //체킹용 변수들 작업.
				globalT = recTerm*cnt;
				cnt++;
				printf("cnt: %d\n", cnt);
				
				//printf("thread join : %d, %s\n", status, fileName);

				//폴더 용량 확인해서 지우기
				kill(pid, SIGUSR2);
                printf("\n\n");
			}
			
		}
		//pthread_join(p_thread[0], (void**)&status);
		//signal(SIGUSR1, NULL);	//프로그램 죽었는지 확인 signal 
		//pause();
    }
	printf("let sigint");
    //마지막으로 빈폴더 검사후 삭제해주는 함수호출
	kill(pid, SIGINT);
    signal(SIGCHLD,SIG_DFL);
	sleep(2);
	kill(pid,SIGKILL);

	return 0;
}

//g++ -o videoRec videoRec.cpp $(pkg-config opencv --libs --cflags)
