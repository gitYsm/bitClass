#include <stdio.h>
#include <time.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
<<<<<<< HEAD
#include <signal.h>
void force_directory( char *a_dirc);
//int mkdirs(const char *path, mode_t mode);
void rmdirs(char *a_dirc);
int main(){

    signal(SIGUSR1, force_directory);
    signal(SIGUSR2, rmdirs);
    
    printf("\n 폴더명 구하기");
    // char parentFolder[100];
    // char downFolder[100];
    // char dir[256] = "/home/ysm/bitClass/bRec";
    // time_t current;
    // current = time(NULL);
    // struct tm *t = localtime(&current);
    // printf("%d년 %d월 %d일 ",
    //     1900 + t->tm_year, t->tm_mon + 1, t->tm_mday);

    // sprintf(parentFolder,"/%d%.2d%.2d",t->tm_year + 1900,(t->tm_mon + 1),t->tm_mday);
    // sprintf(downFolder,"/%d%.2d%.2d_%.2d",t->tm_year + 1900,(t->tm_mon + 1),t->tm_mday,t->tm_hour);
    // strcat(dir, parentFolder);
    // strcat(dir, downFolder);
    // printf("buf: %s \n",dir);
	
=======

void force_directory( char *a_dirc);
int mkdirs(const char *path, mode_t mode);

int main(){
    printf("\n 폴더명 구하기");
    char parentFolder[100];
    char downFolder[100];
    char dir[256] = "/home/ysm/bitClass/bBox";
    time_t current;
    current = time(NULL);
    struct tm *t = localtime(&current);
    printf("%d년 %d월 %d일 ",
        1900 + t->tm_year, t->tm_mon + 1, t->tm_mday);

    sprintf(parentFolder,"/%d%.2d%.2d",t->tm_year + 1900,(t->tm_mon + 1),t->tm_mday);
    sprintf(downFolder,"/%d%.2d%.2d_%.2d",t->tm_year + 1900,(t->tm_mon + 1),t->tm_mday,t->tm_hour);
    strcat(dir, parentFolder);
    strcat(dir, downFolder);
    printf("buf: %s \n",dir);
	
    force_directory(dir);
>>>>>>> 2b2d1696f63de521f4e1f7420edde2db9415eded

	
    return 0;
}

void  force_directory( char *a_dirc){

    char    buff[1024];
    int     sz_dirc;
    int     ndx;
<<<<<<< HEAD
    
    char forderName[100];
    char dir[256] = "/home/ysm/bitClass/bRec";
    time_t current;
    current = time(NULL);
    struct tm *t = localtime(&current);

    sprintf(forderName,"/%d%.2d%.2d_%.2d",t->tm_year + 1900,(t->tm_mon + 1),t->tm_mday,t->tm_hour);
    strcat(dir, forderName);
    printf("buf: %s \n",dir);
    sz_dirc = strlen( dir);

=======

    sz_dirc = strlen( a_dirc);
>>>>>>> 2b2d1696f63de521f4e1f7420edde2db9415eded
    for ( ndx = 1; ndx < sz_dirc; ndx++){
        if ( '/' == a_dirc[ndx]){
            a_dirc[ndx] = '\0';
            sprintf( buff, "%s", a_dirc);
            if ( 0 != access( buff, F_OK)){
                mkdir( buff, 0777);
            }
            a_dirc[ndx] = '/';
        }
    }
    if ( 0 != access( a_dirc, F_OK)){
        mkdir( a_dirc, 0777);
    }
}

<<<<<<< HEAD


=======
>>>>>>> 2b2d1696f63de521f4e1f7420edde2db9415eded
// int mkdirs(const char *path, mode_t mode)
// {
//     char tmp_path[2048];
//     const char *tmp = path;
//     int  len  = 0;
//     int  ret;

//     if(path == NULL || strlen(path) >= 2048) {
//         return -1;
//     }

//     while((tmp = strchr(tmp, '/')) != NULL) {
//         len = tmp - path;
//         tmp++;
//         if(len == 0) {
//             continue;
//         }
//         strncpy(tmp_path, path, len);
//         tmp_path[len] = 0x00;

//         if((ret = mkdir(tmp_path, mode)) == -1) {
//             if(errno != EEXIST) {
//                 return -1;
//             }
//         }
//     }

//     return mkdir(path, mode);
// }