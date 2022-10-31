#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char **argv) {
  //функция, способная принимать аргументы командной строки
  // struct option opts[] = {
  //     {"brackets", no_argument, &is_brackets, 1}, {0, 0, 0, 0},
  //     //{0, 0, 0, 0} стандартный способ указания конца массива структур
  // };
  int bflag=0, eflag=0, nflag=0, sflag=0;
  int opt;
  int flag = 0;
  FILE *fp;
  const int buffersize = 4096;
  char buffer[buffersize];
  int currentfile = (argc > 1 ? 1 : 0);

    while ((opt = getopt(argc, argv, "bens")) !=-1){
    switch(opt){
      case 'b':
      bflag=1;
      break;
      case 'e':
      eflag=1;
      break;
      case 'n':
      nflag=1;
      break;
      case 's':
      sflag=1;
      break;
    }
  }

  while (currentfile < argc) {
    if (argc > 1) {
      fp = fopen(argv[currentfile], "rb"); //открытие для записи и чтения
      if (fp == NULL) {
        printf("No such file or directory");
        flag = 1;
      }
    }
    while (fgets(buffer, buffersize, (fp == NULL ? stdin : fp))) {
      int length = strlen(buffer);
      //последний аргумент fgets указатель на объект типа FILE
      // strlen длина строки не включая завершающий нулевой символ
      buffer[length - 1] = '\0';
      // перезаписали перенос каректки на \0
      // if (sflag){
      // length= strlen
      // }
      fprintf(stdout, "%s\n", buffer);
    }
    fclose(fp);
    currentfile++;
  }
  // while (-1 != (opchar = getopt_long(argc, argv, "bens?", opts, &opindex))) {
  //   switch (opchar) {
  //   case 'b':
  //     break;
  //   }
  // }
  return flag;
}