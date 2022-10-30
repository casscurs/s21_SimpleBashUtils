#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <unistd.h>
// argv-argument vector массив всех элементов, которые получила командная строка
// argc- argumnet count чило аргументов
int main(
    int argc,
    char **argv) { //функция, способная принимать аргументы командной строки
  int flag = 0;
  FILE *fp;
  const int buffersize = 4096;
  char buffer[buffersize];
  int currentfile=(argc>1 ? 1:0);

while (currentfile<argc){
  if (argc > 1) {
    fp = fopen(argv[currentfile], "rb"); //открытие для записи и чтения
    if (fp == NULL) {
      printf("No such file or directory");
      flag = 1;
    }
  }
  while (fgets(buffer, buffersize, (fp == NULL ? stdin : fp))) {  //последний аргумент fgets указатель на объект типа FILE
    int length =
        strlen(buffer); //длина строки не включая завершающий нулевой символ
    buffer[length - 1] = '\0'; // перезаписали перенос каректки на \0
    fprintf(stdout, "%s\n", buffer);
  }
  fclose(fp);
  currentfile++;
}
  return flag;
}
