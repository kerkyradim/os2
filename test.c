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
#include <regex.h>

int main(){
int counter=1;
char str[1000];
const char *parent_expression="^parent pid: +([0-9]+)\n$";
const char *child_expression="i am the child with pid: +([0-9]+) from parent: +([0-9]+)\n$";
char *pstr;
regex_t reegex;
regex_t reegex1;
int value;
int value2;

FILE *ptr=fopen("testc","r");
if(ptr == NULL){
        printf("no such file");
        exit(1);
}
while(1){
        if(!fgets(str,sizeof str,ptr)) break;

        printf("Line %d ",counter);

        counter++;
        pstr=str;
        if(*pstr == '\n') break;

        value=regcomp(&reegex,parent_expression,REG_EXTENDED);
        value2=regcomp(&reegex1,child_expression,REG_EXTENDED);

        if(regexec(&reegex,str,0,NULL,0)){
                printf(" is correct\n");
        }else if(regexec(&reegex1,str,0,NULL,0)){
                printf("is correct\n");
        }else{
                printf("is incorrect\n");
        }
}
}