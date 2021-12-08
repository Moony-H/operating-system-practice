#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    pid_t pid, pidTwo;
    pid = fork();
    //할때마다 바뀐다.
    //줄바꿈은 process를 wait 상태로 가게 만들 수도 있다.
    //it makes different results every time
    //line breaking \n may make process wait
    if (pid > 0)
    {
        printf("hello im parent process \n pid= %d\n", pid);
    }
    else if (pid == 0)
    {
        printf("hello im child process \n pid= %d\n", pid);
    }

    return 0;
}