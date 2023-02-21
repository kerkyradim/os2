#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/file.h>
int main(){

        //creating two pipes
        int pipe1fd[2],pipe2fd[2];
        int status1,status2;
        int pid;

        char parentwrite[50]="Hi child , i am your father";
        char childwrite[50]="Hello from child";
        char readmessage[50];

        //open pipes
        status1=pipe(pipe1fd);
        if(status1 == -1){
                printf("error opening pipe\n");
                exit(1);
        }

        status2=pipe(pipe2fd);
        if (status2 == -1){
                printf("error opening pipe\n");
                exit(1);
        }
for(int i=0; i<3; i++){
        pid=fork();

        //parent process
        if(pid !=0 ){
                close(pipe1fd[0]);//close read side(parent) of pipe1 
                close(pipe2fd[1]);//close write side(parent) of pipe2
           //parent writes message
                printf("parent writing to child with pid:%d  message:%s\n",getpid(),parentwrite);
                write(pipe1fd[1],parentwrite,sizeof(parentwrite));

                //parent reads from pipe 
                read(pipe2fd[0],readmessage,sizeof(readmessage));
                printf("parent reads from child:%d message:%s\n",getpid(),readmessage);

        }else{ //child process
                close(pipe1fd[1]);//close write side(child) of pipe1
                close(pipe2fd[0]);//close read side(child) of pipe2

                //child reading from pipe;
                read(pipe1fd[0],readmessage,sizeof(readmessage));
                printf("child with pid:%d is reading message:%s\n",getpid(),readmessage);


                //child writes to pipe
                printf ("child with pid:%d is writing a message:%s\n",getpid(),childwrite);
                write(pipe2fd[1],childwrite,sizeof(childwrite));
		//exit(0);
        }
int status;
wait(&status);
}
return 0;
}       
