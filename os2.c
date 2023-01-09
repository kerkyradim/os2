#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <limits.h>
#include <time.h>
#include <fcntl.h>
#include <sys/file.h>
#include <string.h>
#include <sys/wait.h>

int main(int argc,char *argv[]){
    FILE *fp;
    int pid;

    int number=atoi(argv[2]);
    fp = fopen(argv[1],"w+");

    int i;
    fprintf(fp,"parent pid: %d\n", getpid());
    fflush(fp);//write parent pid directly in the file and not firstly at the buffer
    for (i=0; i<number; i++){
        if(fork() == 0){
            fprintf(fp,"i am the child with pid:%d from parent:%d\n",getpid(),getppid());
            exit(0);       }
        int status;
        wait(&status); //wait every child
    }
}