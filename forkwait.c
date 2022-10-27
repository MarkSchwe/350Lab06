#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

//variation of the previous fork1.c program that is modified to use the wait() system call.

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

int main(int argc,char **argv)
{
    if(argc != 5){
        printf("not enough variables.");
        exit(-1);
    }
    int Nc = strtoint(argv[1]);
    int Np = strtoint(argv[2]);
    int Tc = strtoint(argv[3]);
    int Tp = strtoint(argv[4]);
pid_t pid;
char *message;
int n;
int exitc;
printf("fork program starting\n");
pid = fork();
switch(pid) 
{
case -1:
    perror("fork failed");
    exit(1);
case 0:
    message = "This is the child";
    n = Nc;
    exitc = 37;
    break;
default:
    message = "This is the parent";
    n = Np;
    exitc = 0;
break;
}
for(; n > 0; n--) {
    puts(message);
    if(n == Nc){
        sleep(Tc);
    }
    if(n == Np){
        sleep(Tp);
    }
}
if (pid != 0) {
    //new section
    int stat_val;
    pid_t child_pid;
    child_pid = wait(&stat_val);
    printf("Child has finished: PID = %d\n", child_pid);
    if(WIFEXITED(stat_val)){
printf("Child exited with code %d\n", WEXITSTATUS(stat_val));
    }else{
printf("Child terminated abnormally\n");
}
}
exit(exitc);
}

//next parent waits until previous child process has finished before running, which is the main difference between
//fork1.c and forkwait.c

