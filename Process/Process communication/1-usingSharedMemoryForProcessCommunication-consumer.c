#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>

int main()
{
    const int SIZE = 4096;   //the size of shared memory 공유 메모리 크기
    const char* name = "OS"; //name of shared memory 공유 메모리 이름

    int shm_fd; // file descriptor
    char* ptr;  //pointer or shared memory

    //공유 메모리 오브젝트 생성
    //create the shared memory object
    shm_fd = shm_open(name, O_RDONLY, 0666);

    //공유 메모리 매핑
    //map the shared memory object
    ptr = (char*)mmap(0, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);

    //포인터를 통해 공유메모리에서 데이터 읽기.
    //read from shared memory through pointer
    printf("%s", (char*)ptr);

    //공유 메모리 지우기
    //remove the shared memory
    shm_unlink(name);

    return 0;
}