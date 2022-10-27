#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>
#include <errno.h>

//variation of forkwait.c that makes use of the exec() system call to call the program child.c

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

//function that converts an integer into a string.
int convIntToStr(char *str, int x){
sprintf(str, "%d", x);
return (strlen(str));
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
char *a;
int exitc;
printf("fork program starting\n");
pid = vfork();
switch(pid) 
{
case -1:
    perror("fork failed");
    exit(1);
case 0:
message = "This is the child and its PID is ";
char **args;
int ir;
char *ar1 = argv[1];
char *ar2 = argv[3];
if (execl ("./child","./forkExec",message,ar1,ar2,NULL) <0) { 
printf ("execl ERROR");
int err = errno;
printf("%d",err);
exit (1);
}
printf("this is the end of the child. \n");
default:
    message = "This is the parent and its PID is ";
    n = Np;
    exitc = 0;
break;
}
//this section in the parent process adds the PID onto the end of the message by concatenating the two 
//strings.
int al = convIntToStr(a,getpid());
char total[al + strlen(message)];
for(int i = 0; i < strlen(message); i++){
    total[i] = message[i];
}
for(int i = 0; i < al; i++){
    total[strlen(message) + i] = a[i];
}
for(; n > 0; n--) {
    puts(total);
    if(n == Np){
        sleep(Tp);
    }
}
if (pid != 0) {
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
