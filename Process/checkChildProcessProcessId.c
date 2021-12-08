#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    pid_t pid;
    pid = fork();
    //무한루프 되지 않는다. fork를 하면 fork의 다음 라인부터 자식 프로세스가 실행된다.즉 여기서 부터 자식 프로세스 시작
    //its not infinite loop. beacause child process execute from next line of fork
    printf("hello %d\n", pid);
    return 0;
}