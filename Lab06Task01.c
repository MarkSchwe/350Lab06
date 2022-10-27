#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

extern char **environ;

/*program that simulates the getenv() system call using the same parameters as the original.*/

char *mygetenv(char *e){
    if(e == ""){
        return "empty string.\n";
    }
    int size1 = 0;
    while(e[size1] != '\0'){
        size1++;
    }
    char **p = environ;
    int size = 0;
    while(p[size] != NULL){
        size++;
    }
    for(int l = 0; l < size; l++){
    int is = 0;
    for(int i = 0; i < size1; i++){
        if(p[l][i] != e[i]){
            is = 1;
        }
    }
    if(is == 0){
        return p[l];
    }
    }
return "variable not found\n";
}

//main function. also has a loop that makes it so input is not case sensitive.
int main(int argc, char **argv){
    if(argc != 2){
        printf("Not enough paramters. (only 1)\n");
        return -1;
    }
   int size = 0;
   while(argv[1][size] != '\0'){
    size++;
   }
    for(int i = 0; i < size; i++){
        if (argv[1][i] >= 'a' || argv[1][i] <= 'z'){
            argv[1][i] = argv[1][i] - 32;
        }
    }
    printf("%s\n",mygetenv(argv[1]));
    exit(0);
}
