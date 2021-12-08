#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    pid_t pid;
    pid = fork();

    //무한루프 되지 않는다. fork를 하면 fork의 다음 라인부터 자식 프로세스가 실행된다.즉 여기서 부터 자식 프로세스 시작
    // 자식 프로세스의 pid는 0이 된다.
    //its not infinite loop. beacause child process execute from next line of fork
    //child process id is zero
    if (pid > 0)
    {
        printf("im parent. pid: %d\n", pid);
    }

    if (pid == 0)
    {
        printf("im child. pid: %d\n", pid);
    }

    return 0;
}