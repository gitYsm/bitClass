#include <stdio.h>
#include <time.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <libgen.h>
#include <sys/vfs.h>

#include <dirent.h>
#include <pwd.h>	// getpwuid()
#include <grp.h>	// getgrgid()
#include <sys/ioctl.h>

void force_directory(int sig);
//int mkdirs(const char *path, mode_t mode);
void rmdirs(int sig);
void getRmDir();
void chkLastfolder();
const char *MMOUNT = "/proc/mounts";

struct f_size
{
    long blocks;
    long avail; 
};

typedef struct _mountinfo 
{
    FILE *fp;                // 파일 스트림 포인터    
    char devname[80];        // 장치 이름
    char mountdir[80];        // 마운트 디렉토리 이름
    char fstype[12];        // 파일 시스템 타입
    struct f_size size;        // 파일 시스템의 총크기/사용율 
} MOUNTP;

MOUNTP *dfopen()
{
    MOUNTP *MP;

    // /proc/mounts 파일을 연다.
    MP = (MOUNTP *)malloc(sizeof(MOUNTP));
    if(!(MP->fp = fopen(MMOUNT, "r")))
    {
        return NULL;
    }
    else
        return MP;
}

MOUNTP *dfget(MOUNTP *MP)
{
    char buf[256];
    char *bname;
    char null[16];
    struct statfs lstatfs;
    struct stat lstat; 
    int is_root = 0;

    // /proc/mounts로 부터 마운트된 파티션의 정보를 얻어온다.
    while(fgets(buf, 255, MP->fp))
    {
        is_root = 0;
        sscanf(buf, "%s%s%s",MP->devname, MP->mountdir, MP->fstype);
         if (strcmp(MP->mountdir,"/") == 0) is_root=1;
        if (stat(MP->devname, &lstat) == 0 || is_root)
        {
            if (strstr(buf, MP->mountdir) && S_ISBLK(lstat.st_mode) || is_root)
            {
                // 파일시스템의 총 할당된 크기와 사용량을 구한다.        
                statfs(MP->mountdir, &lstatfs);
                MP->size.blocks = lstatfs.f_blocks * (lstatfs.f_bsize/1024); 
                MP->size.avail  = lstatfs.f_bavail * (lstatfs.f_bsize/1024); 
                return MP;
            }
        }
    }
    rewind(MP->fp);
    return NULL;
}

int dfclose(MOUNTP *MP)
{
    fclose(MP->fp);
}
void access_perm(char *perm, mode_t mode)
{
	int i;
	char permchar[] = "rwx";
	memset(perm, '-', 10);
	perm[10] = '\0';

	if (S_ISDIR(mode)) perm[0] = 'd';
	else if (S_ISCHR(mode)) perm[0] = 'c';
	else if (S_ISBLK(mode)) perm[0] = 'b';
	else if (S_ISFIFO(mode)) perm[0] = 'p';
	else if (S_ISLNK(mode)) perm[0] = 'l';

	for (i = 0; i < 9; i++) 
	{
		if ((mode << i) & 0x100)
			perm[i+1] = permchar[i%3];
	}

	if (mode & S_ISUID) perm[3] = 's';
	if (mode & S_ISGID) perm[6] = 's';
	if (mode & S_ISVTX) perm[9] = 't';
}

int finish = 1;
int main(){

    signal(SIGUSR1, force_directory);
    signal(SIGUSR2, rmdirs);
    signal(SIGINT, chkLastfolder);
    
    printf("프로세스 생성\n ");
    fflush;
    //처음실행시 용량확인, 경로생성
    rmdirs(1);
    force_directory(1);
    //force_directory(3);   //sig 테스팅 함수
    //시그널 받을때 마다 실행(pause)
    while(1){
        if(finish == 1){
            pause();
        }
    }
	
    return 0;
}

//부모 프로세스 종료시 빈폴더 있나 확인, 삭제
void chkLastfolder(int sig){
    printf("chkLastfolder : %d\n", sig);
    getRmDir(sig);
    finish = 0;
}
//용량 확인하여 경로 삭제 함수로 이동.
void rmdirs(int sig){
    
    MOUNTP *MP;
    if ((MP=dfopen()) == NULL)
    {
        perror("error");
    }

    while(dfget(MP))
    {
        if(strcmp(MP->mountdir, "/") == 0){
            printf("남은 용량 %lf\n", (double)MP->size.avail*100/MP->size.blocks);
            fflush;
            if((double)MP->size.avail*100/MP->size.blocks < 30){
                printf("용량 30%% 미만 : 삭제\n");
                getRmDir(sig);
            }
        }
        
    }
}
#define PERM_LENGTH 	11
#define PATH_LENGTH 	100
#define DEBUG

//폴더 삭제.
void getRmDir(int sig){
    DIR *dp;		// DIR pointer
	struct stat statbuf;	// inode info
	struct dirent *dent;
	struct group *group_entry;
	struct passwd *user_pw;

	char perm[PERM_LENGTH];
	char pathname[PATH_LENGTH];
	char dirname[PATH_LENGTH] = "/home/yang/bitClass/bRec";
    char rmDir[300];
    char rmFile[500];
	int flag;
	char temp[20];

	//time
	struct tm *tm;
    stat(dirname, &statbuf);
    printf("dir: %s\n", dirname);
	// 디렉토리가 아닌경우 에러 메시지 출력 후 종료
	if (!S_ISDIR(statbuf.st_mode)) 
	{
        fprintf(stderr, "%s is not directory\n",dirname);
		exit(1);
	}
	// 디렉토리가 정상적으로 열리지 않은 경우
	if ((dp = opendir(dirname)) == NULL) 
	{
		perror("Error:");
		exit(1);
	}
    struct dirent ** namelist;
	int count;
	int idx;
    
    if((count = scandir(dirname, &namelist, 0, alphasort)) != -1) 
	{
        if(sig == 2){
            sprintf(rmDir,"%s/%s",dirname, namelist[count-1]->d_name);
            printf("sig = 2: %s\n\n", rmDir);
            count = scandir(rmDir, &namelist, 0, alphasort);
            printf("sig = 2 : 내부파일 개수 : %d\n", count);
            if(count == 2){
                int nResult = rmdir(rmDir);
            }
        } else {
            for(idx = 0; idx < count; idx++){
                printf("scan: %s\n",namelist[idx]->d_name);
                fflush;
                if( namelist[idx]->d_name[0] == '.'){
            
                } else {

                    sprintf(rmDir,"%s/%s",dirname, namelist[idx]->d_name);
                    printf("rmDir: %s\n\n", rmDir);
                    if ((dp = opendir(rmDir)) == NULL) 
                    {
                        perror("Error:");
                        exit(1);
                    }
                    while((namelist[idx] = readdir(dp)) != NULL) 
                    {
                        if( (namelist[idx]->d_name)[0] != '.'){
                            sprintf(rmFile,"%s/%s",rmDir, namelist[idx]->d_name);
                            printf("rm fileName:: %s\n", rmFile);
                            
                            int nResult = remove(rmFile);

                            if( nResult == 0 )
                            {
                                printf( "폴더 삭제 성공" );
                            }
                            else if( nResult == -1 )
                            {
                                perror( "폴더 삭제 실패 - 폴더 안에 파일이 있거나 사용중\n" );
                                printf( "errorno : %d", errno );
                            }
                        } 
                    
                        
                    }
                    int nResult = rmdir(rmDir);
                    break;
                }
            }
        }
    }
    
	printf("\n");
	closedir(dp);
    //avail mem research
    rmdirs(sig);
}

void  force_directory(int sig){

    char    buff[32];
    int     sz_dirc;
    int     ndx;
    printf("lets mkdir \n");
    fflush;
    char forderName[64];
    char dir[128] = "/home/yang/bitClass/bRec";
    time_t current;
    current = time(NULL);
    struct tm *t = localtime(&current);
    //if(sig == 1){
    printf("first\n");
    sprintf(forderName,"/%d%.2d%.2d_%.2d",t->tm_year + 1900,(t->tm_mon + 1),t->tm_mday,(t->tm_hour));
    // } else {
    //     printf("sig kill\n");
    //     char  buff[128];
    //     FILE *fp;

    //     fp = popen( "echo `date -d '1 hour' '+/%Y%m%d_%H'`", "r");
    //     if ( NULL == fp)
    //     {
    //         perror( "popen() 실패");
    //     }

    //     while( fgets( buff, 128, fp) )
    //         printf( "buff: %s\n", buff);
    //     buff[12] = '\0';
    //     strcat(forderName, buff);

    //     printf("popen!!! : %s \n", forderName);
    //     pclose( fp);
    // }
    
    strcat(dir, forderName);
    printf("mkdir: %s \n",dir);
    sz_dirc = strlen( dir);

    for ( ndx = 1; ndx < sz_dirc; ndx++){
        
        if ( '/' == dir[ndx]){
            dir[ndx] = '\0';
            sprintf( buff, "%s", dir);
            
            if ( 0 != access( buff, F_OK)){
                printf("dircant access: %d, dir[ndx]: %s\n",ndx,buff);
                mkdir( buff, 0777);
            }
            dir[ndx] = '/';
        }
    }
    if ( 0 != access( dir, F_OK)){
        mkdir( dir, 0777);
    }
}