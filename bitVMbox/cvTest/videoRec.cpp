#include <opencv2/opencv.hpp>
#include <iostream>
#include <time.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <pthread.h>

using namespace cv;
using namespace std;

<<<<<<< HEAD
int main()
{
	pid_t pid;
	int status;
	if((pid=fork())==0)	//자식 프로세스1 라이터, 폴더 용량검사 미리 열어놓기
    {
		int ret;
        //실행시 용량 검사와 저장 폴더 확인 및 생성
		ret = execlp("./bBox", "bBox", NULL);
    }
    else{	//부모 프로세스 비디오 녹화수행.
		
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
		VideoCapture cap("rec.mp4");
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
		writer.open(fileDir, VideoWriter::fourcc('M', 'J', 'P', 'G'), fps, size, true);
		if (!writer.isOpened())
		{
			cout << "동영상을 저장하기 위한 초기화 작업 중 에러 발생" << endl;
			exit(0);
		}

=======
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
		
>>>>>>> 2b2d1696f63de521f4e1f7420edde2db9415eded
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
<<<<<<< HEAD
			end = time(NULL); // 시간 측정 끝
			
            //frame에 시간 넣기
            // center the text
			//Point textOrg((test.cols - size.width)/2,(test.rows + size.height)/2);
			Point textOrg((size.width)/ 2, (size.height) - 10);

			t = localtime(&end);
			sprintf(imgString,"%d-%.2d-%.2d %.2d:%.2d:%.2d",t->tm_year + 1900,(t->tm_mon + 1),t->tm_mday, t->tm_hour, t->tm_min, t->tm_sec);
			int thickness = 2;
			putText(test, imgString, textOrg, FONT_HERSHEY_PLAIN, 2, Scalar::all(255), thickness, 8);
	
			if (test.empty()) {
				cerr << "2빈 영상이 캡쳐되었습니다.\n";
				break;
			}
			
			imshow("Color", test);
			writer.write(test);

			if (waitKey(33) == 27)
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
				writer.open(fileDir, VideoWriter::fourcc('M', 'J', 'P', 'G'), fps, size, true);	
				
                //체킹용 변수들 작업.
				globalT = recTerm*cnt;
				cnt++;
				printf("cnt: %d\n", cnt);
				
				//printf("thread join : %d, %s\n", status, fileName);

				//폴더 용량 확인해서 지우기
				kill(pid, SIGUSR2);
                printf("\n\n");
=======
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
			
>>>>>>> 2b2d1696f63de521f4e1f7420edde2db9415eded
			}
			
		}
		//pthread_join(p_thread[0], (void**)&status);
		//signal(SIGUSR1, NULL);	//프로그램 죽었는지 확인 signal 
		//pause();
    }
<<<<<<< HEAD
	printf("let sigint");
    //마지막으로 빈폴더 검사후 삭제해주는 함수호출
	kill(pid, SIGINT);

	sleep(10);
	kill(pid,SIGKILL);

=======
	
>>>>>>> 2b2d1696f63de521f4e1f7420edde2db9415eded
	return 0;
}

//g++ -o videoRec videoRec.cpp $(pkg-config opencv --libs --cflags)
