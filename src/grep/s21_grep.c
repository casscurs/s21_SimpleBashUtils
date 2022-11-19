#include "s21_grep.h"

//обернуть в if для flag
// cppcheck

int main(int argc, char **argv) {
  int flag = 0;
  opt options = {0};
  size_t sizeStr = 1024;
  char strSearch[sizeSearch] = {0};
  char strPattern[sizeSearch] = {0};
  char *strStr = NULL;
  int redStr = 0;
  strStr = (char *)malloc(sizeStr * sizeof *strStr);

  malloc_check(&strStr, &flag);
  argc_check(argc, &flag);
  flag_turn(argc, argv, &options, strPattern, &flag);
  if (!flag){
  last_sym_rewrite(strPattern);
  int find = optind;
  FILE *fp = NULL;
  int green = 0;
  regex_t regex;
  int registflag = REG_EXTENDED;

  // int opposflag = REG_NOMATCH;
  // int countStr = 0;
  // int fnameflag = 0;
  // int success = 0;

  decrement_optind(&find, options);
  // printf("\n%s\n", strPattern);

  while (find < argc) {
    int Nullflag = 0;
    strcpy(strSearch, argv[find]);
    file_check(argv[++find], &Nullflag, &fp);
    if_E_or_F(options, strPattern, strSearch);
    while (!Nullflag && ((redStr = getline(&strStr, &sizeStr, fp)) != -1) &&
           !options.lflag) {
      regcomp(&regex, strSearch, registflag);

      green = regexec(&regex, strStr, 0, NULL, registflag);

      if ((green == 0)) {
        printf("%s", strStr);
      }
      
    }
    fclose(fp);
    find++;
  }
  regfree(&regex);
  }
  if (strStr != NULL) {
    free(strStr);
  }
  return flag;
}

void flag_turn(int argc, char **argv, opt *options, char *strPattern,
               int *flag) {
  int opchar = 0;
  int opindex = 0;
  while (-1 !=
         (opchar = getopt_long(argc, argv, "+e:ivclnhsf:o", opts, &opindex))) {
switchcase(&opchar,strPattern,options,flag);
  }
}
//  countStr++;
//       printf("%s",strPattern);
//       regcomp(&regex, strStr, registflag);

//       if ((argc-optind)>1){
//         fnameflag=1;
//       }
//       if(options.hflag){
//       fnameflag=0;
//     }
//       if (options.iflag) {
//         registflag = REG_EXTENDED | REG_ICASE;
//       }
//       if (options.vflag) {
//         opposflag =0;
//       }
//       green = regexec(&regex, strStr, 0, NULL, registflag);
//       if (green == opposflag){
//         success++;
//       }
//       if ((green == opposflag) && options.lflag) {//печать только имени файла
//         printf("%s", argv[currfile]);
//       }
//       if ((green == opposflag) && fnameflag && !options.lflag &&
//       !options.cflag && !options.oflag) {//печать с именем файла
//         printf("%s:", argv[currfile]);
//         if (options.nflag) {
//           printf("%d:", countStr);
//         }
//         printf("%s", strStr);
//       }
//       if ((green == opposflag) && !fnameflag && !options.lflag &&
//       !options.cflag && !options.oflag) {//печать без имени файла
//         if (options.nflag) {
//           printf("%d:", countStr);
//         }
//         printf("%s", strStr);
//       }
//       if (options.oflag){ //печать под -o flag
//         for(int i=0;strStr[i] != '\0';i++){
//           if(strspn(&strStr[i],strSearch) >=1){
//             putchar(strStr[i]);
//             putchar('\n');
//           }
//         }
//       }
// if(options.cflag && !Nullflag){// печать успешных
//   if(fnameflag){
//     printf("%s:", argv[currfile]);
//   }
//   printf("%d\n", success);
// }
void malloc_check(char **strStr, int *flag) {
  if (*strStr == NULL) {
    printf("memory error");
    *flag = 1;
  }
}
void last_sym_rewrite(char *strPattern) {
  if ((strPattern) != NULL) {
    int length = strlen(strPattern);
    strPattern[length - 1] = '\0';
  }
}
void decrement_optind(int *find, opt options) {
  if (options.eflag || options.fflag) {
    (*find)--;
  }
}
void if_E_or_F(opt options, char *strPattern, char *strSearch) {
  if (options.eflag || options.fflag) {
    strcpy(strSearch, strPattern);
  }
}
void Ecase(char *strPattern, char *str) {
  strcat(strPattern, str);
  strcat(strPattern, "|");
}
void argc_check(int argc, int *flag) {
  if (argc < 3) {
    printf("too few arguments");
    *flag = 1;
  }
}
void file_check(char *str, int *Nullflag, FILE **fp) {
  *fp = fopen(str, "r");
  if ((*fp) == NULL) {
    printf("grep: %s: No such file\n", str);
    *Nullflag = 1;
  } else {
    *Nullflag = 0;
  }
}
void Fcase(int *flag, char *strPattern) {
  FILE *fpattern = NULL;
  char *strFile = NULL;
  size_t sizeStr = 1024;
  int getCheck = 0;
  strFile = (char *)malloc(sizeStr * sizeof *strFile);
  malloc_check(&strFile, flag);
  if (!(*flag)) {
    fpattern = fopen(optarg, "r");
    file_check(optarg, flag, &fpattern);
    while (((getCheck = getline(&strFile, &sizeStr, fpattern)) != -1) &&
           !(*flag)) {
      int length = strlen(strFile);
      if (strFile[length - 1] == '\n') {
        strFile[length - 1] = '\0';
      }
      Ecase(strPattern, strFile);
    }
    fclose(fpattern);
  }
  if (strFile != NULL) {
    free(strFile);
  }
}
void switchcase(int *opchar,char *strPattern,opt *options,int *flag){
      switch (*opchar) {
    case 'e':
      options->eflag = 1;
      Ecase(strPattern, optarg);
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
      Fcase(flag, strPattern);
      break;
    case 'o':
      options->oflag = 1;
      break;
    default:
      printf("usage: grep [-benstuv] [file ...]\n");
    }
}