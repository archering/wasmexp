#include <stdio.h>
#include <string.h>
int main() {
    printf(" this is from c ! \n");
    return 133;
}


int add(int a,int b) {
    return a + b;
}

int doubleit(int a) {
    return a * 2;
}

//special

char * greet(char * name) {
    char * string = "your name is :";
    strcat(string,name);
    return string;
}

char * hello = "this is from math.c";

char * getHello() {
    return hello;
}