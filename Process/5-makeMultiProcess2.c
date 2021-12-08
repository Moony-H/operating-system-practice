#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    //프로세스 16개가 생성된다.
    //it will make 16 process
    int a = 0;
    for (a = 0; a < 4; a++)
    {
        fork();
    }
    printf("hi im process\n");
}