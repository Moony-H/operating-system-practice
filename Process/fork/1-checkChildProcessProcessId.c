#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    pid_t pid;
    pid = fork();

    //���ѷ��� ���� �ʴ´�. fork�� �ϸ� fork�� ���� ���κ��� �ڽ� ���μ����� ����ȴ�.�� ���⼭ ���� �ڽ� ���μ��� ����
    // �ڽ� ���μ����� pid�� 0�� �ȴ�.
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