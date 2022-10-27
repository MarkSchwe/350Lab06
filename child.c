#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>

//program called by forkExec.c which performs the same functions as the child process did in 
//forkwait.c and fork1.c while also taking the message, Nc, and Tc as parameters.

double strtoint(char *f){
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

int main(int argc, char **argv){
char *message = argv[1];
int Nc = strtoint(argv[2]);
int Tc = strtoint(argv[3]);
char *a;

//performs same function as its counterpart in the parent process; to put the PID onto the end of the message.
int al = convIntToStr(a,getpid());
char total[al + strlen(message)];
for(int i = 0; i < strlen(message); i++){
    total[i] = message[i];
}
for(int i = 0; i < al; i++){
    total[strlen(message) + i] = a[i];
}
total[strlen(message)+al] = ' ';
int n = Nc;
//prints out the child's messages
for(;n > 0; n--){
    puts(total);
    if(n == Nc){
        sleep(Tc);
    }
}
exit(0);
}
