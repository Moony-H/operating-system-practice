#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    pid_t pid;
    pid = fork();
    //���ѷ��� ���� �ʴ´�. fork�� �ϸ� fork�� ���� ���κ��� �ڽ� ���μ����� ����ȴ�.�� ���⼭ ���� �ڽ� ���μ��� ����
    //its not infinite loop. beacause child process execute from next line of fork
    printf("hello %d\n", pid);
    return 0;
}