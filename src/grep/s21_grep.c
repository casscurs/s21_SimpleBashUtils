#include "s21_grep.h"

//обернуть в if для flag
// cppcheck

int main(int argc, char **argv) {
  int flag = 0;
  opt options = {0};
  const int sizeSearch = 8192;
  size_t sizeStr = 1024;
  char strSearch[sizeSearch]={0};
  char *strStr;
  int redStr;
  strStr = (char *)malloc(sizeStr * sizeof *strStr);
  if (strStr == NULL) {
    printf("memory error");
    flag = 1;
  }
  argc_check(argc, &flag);
  flag_turn(argc, argv, &options);
  int currfile = optind + 1;
  int find = optind;
  int Nullflag=0;
  FILE *fp = NULL;
  int green;
  regex_t regex;
  int registflag = 0;
  int opposflag = 0;
  int countStr = 0;
  int fnameflag = REG_EXTENDED;
  int success=0;
  while (currfile < argc) {
    strcpy(strSearch, argv[find]); //через /
    file_check(argv, &Nullflag, &fp, &currfile);
    while (!Nullflag && ((redStr = getline(&strStr, &sizeStr, fp)) != -1)&& !options.lflag) {
      countStr++;
      regcomp(&regex, argv[find], registflag);


      if ((argc)>4){
        fnameflag=1;
      }
      if(options.hflag){
      fnameflag=0;
    }
      if (options.iflag) {
        registflag = REG_EXTENDED | REG_ICASE;
      }
      if (options.vflag) {
        opposflag = REG_EXTENDED | REG_NOMATCH;
      }
      green = regexec(&regex, strStr, 0, NULL, registflag);
      if (green == opposflag){
        success++;
      }
      if ((green == opposflag) && options.lflag) {//печать только имени файла
        printf("%s", argv[currfile]);
      }
      if ((green == opposflag) && fnameflag && !options.lflag && !options.cflag && !options.oflag) {//печать с именем файла
        printf("%s:", argv[currfile]);
        if (options.nflag) {
          printf("%d:", countStr);
        }
        printf("%s", strStr);
      }
      if ((green == opposflag) && !fnameflag && !options.lflag && !options.cflag && !options.oflag) {//печать без имени файла
        if (options.nflag) {
          printf("%d:", countStr);
        }
        printf("%s", strStr);
      }
      if (options.oflag){ //печать под -o flag
        for(int i=0;strStr[i] != '\0';i++){
          if(strspn(&strStr[i],strSearch) >=1){
            putchar(strStr[i]);
            putchar('\n');
          }
        }
      }
      if (options.eflag){
        if(strSearch != '\0'){
          strcat(strSearch,'|');
          strcat(strSearch,'');//шаблон
        } else{
          strcopy()//шаблон
        }
      }
    }
      if(options.cflag && !Nullflag){// печать успешных
        if(fnameflag){
          printf("%s:", argv[currfile]);
        }
        printf("%d\n", success);
      }
      success=0;
    fclose(fp);
    Nullflag=0;
    (currfile)++;
    find++;
  }
  free(strStr);
  regfree(&regex);
  return flag;
}

void argc_check(int argc, int *flag) {
  if (argc < 3) {
    printf("too few arguments");
    *flag = 1;
  }
}
void file_check(char **argv, int *Nullflag, FILE **fp, int *currfile) {
    *fp = fopen(argv[(*currfile)], "r");
    if ((*fp) == NULL) {
      printf("grep: %s: No such file\n", argv[(*currfile)]);
      *Nullflag = 1;
    } else {
      *Nullflag = 0;
  }
}
void flag_turn(int argc, char **argv, opt *options) {
  int opchar = 0;
  int opindex = 0;
  while (-1 !=
         (opchar = getopt_long(argc, argv, "+eivclnhsfo", opts, &opindex))) {
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
// int redSearch;
// strSearch=(char*)malloc(sizeSearch * sizeof *strSearch);
//   //чтение поисковой строки
//   redSearch=getline(&strSearch, &sizeSearch,stdin);
//    if (redSearch==-1){
//    printf("line error");
//    flag=1;
//  }
// free(strSearch);