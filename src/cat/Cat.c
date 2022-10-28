#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv){ //функция, способная принимать аргументы командной строки 
int flag=0;
const int buffersize=4096;
char buffer[buffersize];

while(fgets(buffer, buffersize, stdin)){ //последний аргумент fgets указатель на объект типа FILE
    int length=strlen(buffer);//длина строки не включая завершающий нулевой символ
    buffer[length-1]='\0';// перезаписали перенос каректки на \0
    fprintf(stdout, "%s",buffer);
}
return flag;
}