#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char **argv) {
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
  int currentfile;

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
//пока не пройдем все файлы
  currentfile = optind;
  ///
  while (currentfile < argc) {
    if (currentfile!=argc) {
      fp = fopen(argv[currentfile], "rb");
      if (fp == NULL) {
        printf("No such file or directory");
        flag = 1;
      }
    }
    int lastMt=0;
    int lastLineBlank=0;
    //считываем строки
    while (fgets(buffer, buffersize, (fp == NULL ? stdin : fp))) {
      int length = strlen(buffer);
    // перезаписали перенос каректки на \0
      buffer[length - 1] = '\0';

      if (sflag){
         length=strlen(buffer);
         int currMt=0;
         //<=1 тк \n
         if (length<=1)
         currMt=1;
         else
         currMt=0;
        if (currMt != lastMt){
          lastMt=currMt;
        }
                //         length = strlen(buffer);
                // int currentLineBlank = (length <= 1) ? 1 : 0;
                // if (lastLineBlank && currentLineBlank) {
                //     continue;
                // }
                // lastLineBlank = currentLineBlank;
      }

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





 