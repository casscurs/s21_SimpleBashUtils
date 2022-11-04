#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct options {
  int bflag;
  int nflag;
  int eflag;
  int sflag;
  int tflag;
  int vflag;
} opt;

int main(int argc, char **argv) {
  opt options = {0, 0, 0, 0, 0, 0};
  int length;
  int flag = 0,flagin=0;
  int opt;
  FILE *fp = NULL;
  int b_read;
  size_t size = 10;
  char *str;
  int b = 0;
  int opchar = 0;
  int opindex = 0;
  struct option opts[] = {
      {"squeeze-blank", no_argument, 0, 's'},
      {"number-nonblank", no_argument, 0, 'b'},
      {"E", no_argument, 0, 'e'},
      {"number", no_argument, 0, 'n'},
      {"T", no_argument, 0, 't'},
      {0, 0, 0, 0},
  };

  while (-1 != (opchar = getopt_long(argc, argv, "+sbenstv", opts, &opindex))) {
    switch (opchar) {
    case 'b':
      options.bflag = 1;
      break;
    case 'e':
      options.eflag = 1;
      break;
    case 'n':
      options.nflag = 1;
      break;
    case 's':
      options.sflag = 1;
      break;
    case 't':
      options.tflag = 1;
      break;
    case 'v':
      options.vflag = 1;
      break;
    default:
      printf("flag: %c\n", opchar);
    }
  }
  int currfile = optind;
  str = (char *)malloc(size);

  if(argc<=1){
    flagin=1;
  }

  while (currfile <= argc) {
    if (currfile != argc) {
        fp = fopen(argv[currfile], "rb");
      if (fp == NULL) {
        printf("%s: No such file or directory", argv[currfile]);
        flag = 1;
        currfile++;
        continue;
      }
    }
    int lastempt = 0;
    int i = 1;
    int m=1;
    while ((getline(&str, &size, (flagin ? stdin : fp))) != -1) {
      length = strlen(str);
      str[length - 1] = '\0';
            if (options.eflag) {
        length = strlen(str);
        str[length] = '$';
        str[length + 1] = '\0';
      }
      if (options.sflag) {
        length = strlen(str);
        int currempt = 0;
        if (length <= 1) {
          currempt = 1;
        }
        if (lastempt && currempt) {
          continue;
        }
        lastempt = currempt;
      } 
      if (options.bflag) {
        if(strlen(str)>1){
          printf("%*d\t", 6, m);
          m++;
        }
      } else if (options.nflag) {
        printf("%*d\t", 6, i);
      }
      if (options.tflag) {
        length = strlen(str);
        for (int k = 0; k <= length; k++) {
          if (str[k] != '\0') {
            if (str[k] == '\t') {
              printf("^I");
            } else
              putchar(str[k]);
          } else {
            putchar('\n');
          }
        }
      } else
      // if (options.vflag){
      //   length = strlen(str);
      //   for(int k=0;k<=length;k++){
      // }
        fprintf(stdout, "%s\n", str);

      i++;
    }
    fclose(fp);
    currfile++;
  }
  free(str);
  return flag;
}