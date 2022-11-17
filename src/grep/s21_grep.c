#include "s21_grep.h"

//обернуть в if для flag
// cppcheck

int main(int argc, char **argv) {
  int Nullflag = 0;
  int flag = 0;
  opt options = {0};
  size_t sizeStr = 1024;
  char strSearch[sizeSearch] = {0};
  char strPattern[sizeSearch] = {0};
  char *strStr;
  int redStr;
  strStr = (char *)malloc(sizeStr * sizeof *strStr);
  if (strStr == NULL) {
    printf("memory error");
    flag = 1;
  }
  argc_check(argc, &flag);
  flag_turn(argc, argv, &options, strPattern,&Nullflag);

  int find = optind;
  FILE *fp = NULL;
  int green;
  //regex_t regex;
  int registflag = REG_EXTENDED;
  int opposflag = REG_NOMATCH;
  int countStr = 0;
  int fnameflag = 0;
  int success = 0;
  while (find < argc) {
    strcpy(strSearch, argv[find]);
    //printf("%s", strPattern);
    file_check(argv, &Nullflag, &fp, ++find);
    while (!Nullflag && ((redStr = getline(&strStr, &sizeStr, fp)) != -1) &&
           !options.lflag) {
      if (options.eflag || options.fflag) {
        strcpy(strSearch, strPattern);
      }
      //regcomp(&regex, strStr, registflag);
    }
    success = 0;
    fclose(fp);
    Nullflag = 0;
    find++;
  }
  free(strStr);
  //regfree(&regex);
  return flag;
}

void argc_check(int argc, int *flag) {
  if (argc < 3) {
    printf("too few arguments");
    *flag = 1;
  }
}
void file_check(char **argv, int *Nullflag, FILE **fp, int currfile) {
  *fp = fopen(argv[(currfile)], "r");
  if ((*fp) == NULL) {
    printf("grep: %s: No such file\n", argv[(currfile)]);
    *Nullflag = 1;
  } else {
    *Nullflag = 0;
  }
}
void flag_turn(int argc, char **argv, opt *options, char *strPattern,int* Nullflag) {
  int opchar = 0;
  int opindex = 0;
  while (-1 !=
         (opchar = getopt_long(argc, argv, "+e:ivclnhsf:o", opts, &opindex))) {
    switch (opchar) {
    case 'e':
      options->eflag = 1;
     // printf("\n%s\n", optarg);
      strcat(strPattern,optarg);
      strcat(strPattern,"|");
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
  //     options->fflag = 1;
  //           FILE *fpatt=NULL;
  //     fpatt = fopen(optarg, "r");
  // if ((fpatt) == NULL) {
  //   printf("grep: %s: No such file\n", optarg);
  //   *Nullflag = 1;
  // } else {
  //     char *token, *last;
  // token = strtok_r(strPattern, "|", &last);//вернет указатель на найденный токен
  // int f_patt = 0;
  // (void)f_patt;
  // while (token != NULL) {
  //   token = strtok_r(NULL, "|", &last);
  // }
  //   *Nullflag = 0;
  // }
  // printf("\n%s\n", strPattern);
      break;
    case 'o':
      options->oflag = 1;
      break;
    default:
      printf("usage: grep [-benstuv] [file ...]\n");
    }
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