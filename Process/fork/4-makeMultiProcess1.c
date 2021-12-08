#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    //프로세스 8개가 생성된다.
    //it will make 8 process

    fork();
    fork();
    fork();
    printf("im process\n");
}