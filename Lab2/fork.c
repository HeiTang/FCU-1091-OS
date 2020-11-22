#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
    int pid1,pid2;

    printf("Begin Running ...\n");

    pid1 = fork();

    if(pid1 == 0){
        wait(0);
        printf("Child process! ID is %d\n", getpid());
    }
    else if(pid1 > 0){
        pid2 = fork();
        if(pid2 == 0){
            wait(0);
            printf("Child process! ID is %d\n", getpid());
        }
        else if(pid2 > 0){
            wait(0);
            printf("Parent process! ID is %d\n", getpid());
            execlp("/bin/ls","ls",(char*)0);
        }
        else printf("Fork() Error ...\n");
    }
    else printf("Fork() Error ...\n");


    printf ("Ending ...\n");

    exit(0);
}