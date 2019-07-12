#include <stdio.h>

#define  BUFF_SIZE   4

int main( void)
{
    char  buff[BUFF_SIZE];
    FILE *fp;

    fp = popen( "ls -al", "r");
    if ( NULL == fp)
    {
        perror( "popen() 실패");
        return -1;
    }
    int i=0;
    while( fgets( buff, BUFF_SIZE, fp) ){
        if(i==0){
            i++;
            printf( "%s\n", buff);
            break;
        }
        
    }
        
    pclose( fp);
   return 0;
}