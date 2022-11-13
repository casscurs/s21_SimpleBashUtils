#include "s21_grep.h"
//обернуть в if для flag
// if для argc
int main(int argc, char **argv) {
  int flag = 0;
  opt options = {0};
  size_t sizeSearch=1024;
  size_t sizeStr=1024;
  char* strSearch;
  char* strStr;
  int redSearch;
  int redStr;
  // чистый malloc
  strSearch=(char*)malloc(sizeSearch * sizeof *strSearch);
  strStr=(char*)malloc(sizeStr * sizeof *strStr);
  if (strSearch==NULL || strStr==NULL){
    printf("memory error");
    flag=1;
  }
//   redStr=getline(&strStr, &sizeStr,stdin);
//    redSearch=getline(&strSearch, &sizeSearch,stdin);
//     if (redSearch==-1){
//     printf("line error");
//     flag=1;
//   }
  flag_turn(argc, argv, &options);
  int currfile = optind;
  int Nullflag=0;
  FILE *fp = NULL;

// regex_t regex;
// int regflag=0;
// int green;
  while (currfile < argc) {
    if (currfile != argc) {
      fp = fopen(argv[currfile], "r");
      if (fp == NULL) {
        printf("\ngrep: %s: No such file\n", argv[currfile]);
        Nullflag = 1;
        (currfile)++;
        continue;
      } else {
        Nullflag = 0;
      }
    }
while (!Nullflag && ((redStr=getline(&strStr, &sizeStr,fp))!= -1)){
    printf("%s", strStr);
}
    fclose(fp);
    (currfile)++;
  }
//      while ((redStr=getline(&strStr, &sizeStr,fp))!= -1 && !Nullflag){
// regcomp(&regex,strSearch, regflag);
// while(*strStr != EOF ){
//      //printf("sfsfsfsfsf");
//   green=regexec(&regex,strStr, 0, NULL,0);//если все получилось вернет 0
//   if(green==0){
//     printf("%s", strStr);
//   }
// }
//      }
  free(strSearch);
  free(strStr);
  return flag;
}

void flag_turn(int argc, char **argv, opt *options) {
  int opchar = 0;
  int opindex = 0;
  while (-1 != (opchar = getopt_long(argc, argv, "+eivclnhsfo", opts, &opindex))) {
    switch (opchar) {
      case 'e':
        options->eflag = 1;
        break;
      case 'i':
        options->iflag = 1;
        break;
      case 'v':
        options->vflag = 1;
        break;
      case 'c':
        options->cflag = 1;
        break;
      case 'l':
        options->lflag = 1;
        break;
      case 'n':
        options->nflag = 1;
        break;
      case 'h':
        options->hflag = 1;
        break;
      case 's':
        options->sflag = 1;
        break;
      case 'f':
        options->fflag = 1;
        break;
      case 'o':
        options->oflag = 1;
        break;
      default:
        printf("usage: grep [-benstuv] [file ...]\n");
    }
  }
}