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
    const int SIZE = 4096;                     //the size of shared memory 공유 메모리 크기
    const char* name = "OS";                   //name of shared memory 공유 메모리 이름
    const char* message0 = "Hi";               //message 메시지
    const char* message1 = "im shared memory"; //message 메시지

    int shm_fd; // file descriptor
    char* ptr;  //pointer or shared memory

    //공유 메모리 오브젝트 생성(메모리 이름, open 가능한 명령?(flag), 접근 권한)
    //create the shared memory object(name of shared memory, open_flag, permission of access)
    //성공시에 file descriptor를 return 한다.
    //it return file descriptor when it successed
    shm_fd = shm_open(name, O_CREAT | O_RDWR, 0666);

    ftruncate(shm_fd, SIZE); // configure the size or shared memory 메모리 크기 설정.

    //공유 메모리에 매핑. 각 매개변수는 (매핑할 메모리 주소,메모리 공간의 크기,보호 모드, 매핑된 데이터의 처리 방법, 파일 기술자(file descriptor), 파일 오프셋)
    //map the shared memory object parameters are (address of memory to be mapped, the size of memory, protection mode, way of processing data, file descriptor, file offset)
    ptr = (char*)mmap(0, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);

    //write to the shared memory
    sprintf(ptr, "%s", message0);
    //포인터를 올려서 어디까지 메시지를 채웠는지 index(?) 위치 확인
    //message's last index pointer for checking
    ptr += strlen(message0);
    //위와 동일
    sprintf(ptr, "%s", message1);
    ptr += strlen(message1);
    return 0;