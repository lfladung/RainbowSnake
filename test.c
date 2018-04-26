#include <sys.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int a,c;
a = 1;
c = 2;

int main(int argc,char *argv[]){

  if(fork()==0){
    printf("a= %d, c = %d\n", a, c);
    a = 10;
    c = 20;
    wait(NULL);
    printf("a= %d, c = %d\n", a, c);
  }
printf("a= %d, c = %d\n", a, c);

}
