#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

//program that takes a file input and puts output onto a parent and child file. sleep() is unable to be
//used, so i kept continuity by using lseek to force the two processes to run simultaneously by using their 
//respective versions of the variable n.

int strtoint(char *f){
int l = 0;
int size = 0;
while (f[size] != '\0'){
    size++;
}
for(int i = 0; i < size; i++){
    l = l + (f[i] - '0');
    if(f[i + 1] != '\0'){
        l = l * 10;
    }
}
    return l;
}

//main function
int main(int argc,char **argv)
{
    umask(0);
    if(argc != 2){
        printf("not enough variables.");
        exit(-1);
    }
    int fd1 = open(argv[1],O_RDONLY);
pid_t pid;
char *message;
int n = 0;
int nread = 0;
int nread2 = 0;
int pout, cout = 0;
char b[1];
char b2[1];
printf("fork program starting\n");
pid = fork();
switch(pid) 
{
case -1:
    perror("fork failed");
    exit(1);
case 0:
pout = open("parentout.txt",O_RDWR | O_CREAT,0666);
//puts numerical characters in the output file.
    while((nread = read(fd1,b,1)>0)){
        if(*b >= '0' && *b <= '9'){
            write(pout,b,1); 
        }
        n++;
        lseek(fd1,n,SEEK_SET);
    }
break;
default:
cout = open("childout.txt",O_RDWR | O_CREAT,0666);
//puts non-alphanumerical characters in the output file.
    while((nread2 = read(fd1,b2,1)>0)){
        if(*b2 < '0' || *b2 > '9'){
            write(cout,b2,1);
        }
        n++;
        lseek(fd1,n,SEEK_SET);
    }
break;
}
exit(0);
}
