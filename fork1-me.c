#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

/*copy of fork1.c from the textbook but with the ability to use command line arguments.*/

//function for use to turn command line numbers into integers from character strings.
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
    break;
default:
    message = "This is the parent";
    n = Np;
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
exit(0);
}
