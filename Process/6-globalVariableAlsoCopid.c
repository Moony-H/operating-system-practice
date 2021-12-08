#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int a = 5;

int main()
{

    //이 코드의 결과는 5이다.
    //a변수도 fork를 하면 얕은 복사가 되어 다른 주소값을 가진다.
    //this code's result is 5
    //because the variable a is also copied shallowly when its forked

    pid_t pid;
    pid = fork();
    if (pid > 0)
    {
        wait(NULL);
        printf("%d\n", a);
    }

    if (pid == 0)
    {
        a += 10;
    }
    return 0;
}