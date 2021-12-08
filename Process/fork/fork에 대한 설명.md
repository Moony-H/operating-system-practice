## fork()의 간략한 설명

fork()는 linux, unix에서 사용하는 프로세스를 복제하는 함수이다.

즉, 완전히 같은 프로세스를 하나 더 메모리에 올려 실행 시키는 함수다.

그렇기에 pcb(proc이라는 구조체)에 있는 "현재 어디까지 코드를 실행시켰지?"를 담당하는 부분까지 복사가 된다.

그렇기에 fork()를 하여도(다시 처음부터 실행되지 않기 때문에) 무한히 복제를 하지 않는다.

또한 fok()는 반환값이 있는데,0과 자식pid 값이다.

이 값은 지금 실행시키는 코드가 자식을 생성 하였을 때, 자식의 프로세스와 부모의 프로세스를 구분지을 수 있게 하는 값이다.

즉, 부모는 자식의 pid 값을 가지고 자식은 0을 가져서 fork 후의 코드에서 자신이 부모인지 자식인지를 구분지을 수 있는 수단을 제공하는 것이다.

그렇다면 생각나는 것이 있다.

"분명 똑같이 복제되어서 같은 프로세스일 텐데, fork가 두번 실행 되는 것인가...? 그래야 부모에게는 자식 pid, 자식에게는 0을 줄 수 있을텐데?"

그럼 아래를 보자.

```c
2303 int
2304 fork(void)
2305 {
2306   int i, pid;
2307   struct proc *np; 
2308
2309   // Allocate process.
2310   if((np = allocproc()) == 0) 
2311     return −1;
2312
2313   // Copy process state from p.
2314   if((np−>pgdir = copyuvm(proc−>pgdir, proc−>sz)) == 0){  
2315     kfree(np−>kstack);
2316     np−>kstack = 0;
2317     np−>state = UNUSED;
2318   return −1;
2319   }
2320   np−>sz = proc−>sz; 
2321   np−>parent = proc; 
2322   *np−>tf = *proc−>tf;  
2323
2324   
2325   np−>tf−>eax = 0;  //여기가 가장 중요!!
2326                  //자식 프로세스는 리턴값으로 0을 사용하게 됨
2327   for(i = 0; i < NOFILE; i++)
2328     if(proc−>ofile[i])
2329       np−>ofile[i] = filedup(proc−>ofile[i]);
2330   np−>cwd = idup(proc−>cwd);
2331
2332   pid = np−>pid;
2333   np−>state = RUNNABLE;
2334   safestrcpy(np−>name, proc−>name, sizeof(proc−>name));
2335   return pid;
2336 }
```



위는 proc.c 내부의 fork()함수의 정의이다. 2325줄이 중요하다. 프로세스를 복제한 후, 임의로 eax를 0으로 만들고, 이 값을 자식 프로세스는 return 값으로 사용하게 되는 것이다.

흐름을 얘기하자면 fork에서 proc 구조체를 자식에게 복사한 후 부모 process를 wait 시킨다. 그리고 자식프로세스를 위한 proc을 만드는 과정에서 그 값을 수정한다. 이렇게 되면 자식 프로세스가 부모 프로세스보다 먼저 실행 되고, fork의 return 값으로 0이 return 될 수 있다.

간단히 얘기하면 완전히 복제한 다음 커널스택에 수동으로 하나하나 해준다는 뜻이다.

그렇기에 자식으로 구분지을 수 있는 값인 0을 받아 우리는 사용할 수 있게 된다.

생각해 보면 굳이 0으로 구분짓는 방법을 쓰지 않아도 getpid를 이용하여 구분 지을 수는 있다. 밑은 내가 작성한 예시 코드다.

``` c
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>


int main()
{

    pid_t parentPid, nowPid;
    parentPid = getpid();
    fork();
    nowPid = getpid();//parent에서는 위의 parentPid와 같은 값이 들어가고,
    				//child에서는 child의 pid 값이 들어간다.
    if (parentPid == nowPid)
    {
        printf("im parent. pid: %d\n", nowPid);
    }
    else
    {
        printf("im child. pid: %d\n", nowPid);
    }
}
```

이렇게도 사용할 수 있는데, 굳이 왜 만들었을까...? 라고 생각할 수 있지만

옛날의 컴퓨터를 생각하면 이해가 된다.

아마 바이트 단위 하나하나 아껴가며 쓸 상황이 많기 때문에 그럴 것이다.

변수 하나만 사용하여 fork하면 그 변수는 두개가 되지만,

나처럼 변수 두개를 사용하면 그 변수는 네개가 된다.

그렇기에 바이트를 아껴 쓰기 위해 라고 추측(?)해 볼 수 있다.





