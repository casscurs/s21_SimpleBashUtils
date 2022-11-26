#include "s21_grep.h"

// valgrind
// cppcheck
void File_range(opt options, int *Nullflag, int find, FILE **fp) {
  if ((find + 1) >= (options.argc)) {
    *Nullflag = 1;
  } else {
    file_check((options.argv)[1 + find], Nullflag, fp);
  }
}
void free_at_exit(opt *options) {
  if (options->strStr) {
    free(options->strStr);
    options->strStr = NULL;
  }
  if (options->strFile) {
    free(options->strFile);
    options->strFile = NULL;
  }
}

int main(int argc, char **argv) {
  int flag = 0;
  opt options = {0};
  size_t sizeStr = 1024;
  options.argc = argc;
  options.argv = argv;
  options.strStr = (char *)malloc(sizeStr * sizeof options.strStr);
  malloc_check(options.strStr, &options);
  pars_and_prework(&options);
  argc_check(&options);
  last_sym_rewrite(options.strPattern);

  int find = optind;
  regex_t regex;
  regmatch_t pmatch[1];
  int registflag = REG_NEWLINE | REG_EXTENDED;

  decrement_for_EF(&find, options);
  while (find < (argc)) {
    int Nullflag = 0;
    FILE *fp = NULL;
    strcat(options.strSearch, argv[find]);
    if_E_or_F(options, options.strPattern, options.strSearch);
    File_range(options, &Nullflag, find, &fp);

    int Ncount=0;

    while (!Nullflag &&
           ((options.gline = getline(&(options.strStr), &sizeStr, fp)) != -1) &&
           !options.lflag) {
            Ncount+=1;
            if (options.nflag){
              while(Ncount=>1){
                putchar(
              }
            }
            printf("%d",Ncount);
           // printf("%s",options.strBuf );
      int success = 0;

      regcomp(&regex, options.strSearch, registflag);
      options.regFound = regexec(&regex, options.strStr, 1, pmatch, 0);
      if (options.oflag) {
           int line_pos = 0;
        int length = strlen(options.strStr);
        while (regexec(&regex, options.strStr + line_pos, 1, pmatch, 0) == 0) {
          int k = strlen(options.strBuf);
          for (int i = pmatch->rm_so; i < pmatch->rm_eo; i++) {
            options.strBuf[k] = options.strStr[i];
            k++;
          }
          (options.strBuf)[strlen(options.strBuf)] = '\n';
          line_pos = line_pos + pmatch->rm_eo+1;
          if (line_pos > length) {
            break;
          }
        }
      }
      if (options.vflag) {
        success = REG_NOMATCH;
      }
      if ((options.regFound == success) && !options.oflag) {
        int k = strlen(options.strBuf);
        for (size_t i = 0; i < strlen(options.strStr); i++) {
          options.strBuf[k] = options.strStr[i];
          k++;
        }
      }
    }
    if (fp != NULL) {
      fclose(fp);
    }
    find++;

     if (options.vflag) {
    (options.strBuf)[strlen(options.strBuf)] = '\n';
  }
  printf("%s", options.strBuf); 
  }
  //(options.strBuf)[strlen(options.strBuf)]='\n';
  regfree(&regex);
  free_at_exit(&options);
  return flag;
}

void pars_and_prework(opt *options) {
  int opchar = 0;
  int opindex = 0;
  while (-1 != (opchar = getopt_long(options->argc, options->argv,
                                     "e:ivclnhsf:o", opts, &opindex))) {
    switchcase(&opchar, options);
  }
}

void malloc_check(char *str, opt *options) {
  if (str == NULL) {
    perror("memory error");
    free_at_exit(options);
    exit(1);
  }
}

void last_sym_rewrite(char *strPattern) {
  if ((strPattern) != NULL) {
    int length = strlen(strPattern);
    strPattern[length - 1] = '\0';
  }
}

void decrement_for_EF(int *find, opt options) {
  if (options.eflag || options.fflag) {
    (*find) = (*find) - 1;
    options.argc--;
  }
}

void if_E_or_F(opt options, char *strPattern, char *strSearch) {
  if (options.eflag || options.fflag) {
    strcpy(strSearch, strPattern);
  }
}

void Ecase(char *strPattern, char *str) {
  int length = strlen(str);
  if (strlen(str) > 0) {
    if ((length == 1) && (str[length - 1] == '*')) {
      strcpy(str, " *");
    }
    strcat(strPattern, str);
    strcat(strPattern, "|");
  }
}

void argc_check(opt *options) {
  if (options->argc < 3) {
    printf("too few arguments");
    free_at_exit(options);
    exit(1);
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

void file_check_exit(char *str, int *Nullflag, FILE **fp, opt *options) {
  *fp = fopen(str, "r");
  if ((*fp) == NULL) {
    printf("grep: %s: No such file\n", str);
    *Nullflag = 1;
    free_at_exit(options);
    exit(1);
  } else {
    *Nullflag = 0;
  }
}

void Fcase(opt *options) {
  FILE *fpattern = NULL;
  size_t sizeStr = 1024;
  options->strFile = (char *)malloc(sizeStr * sizeof options->strFile);
  int getCheck = 0;
  int Nullflag = 0;
  int starflag = 0;
  malloc_check(options->strFile, options);
  file_check_exit(optarg, &Nullflag, &fpattern, options);
  while (
      ((getCheck = getline(&(options->strFile), &sizeStr, fpattern)) != -1) &&
      (!Nullflag)) {
    int length = strlen(options->strFile);
    if ((strlen(options->strFile) == 1) &&
        ((options->strFile)[length - 1] == '\n') && !starflag) {
      (options->strFile)[length - 1] = '*';
      Ecase(options->strPattern, options->strFile);
      starflag = 1;
    } else {
      if ((options->strFile)[length - 1] == '\n') {
        (options->strFile)[length - 1] = '\0';
        Ecase(options->strPattern, options->strFile);
      } else {
        Ecase(options->strPattern, options->strFile);
      }
    }
  }
  if (fpattern != NULL) {
    fclose(fpattern);
  }
}

void switchcase(int *opchar, opt *options) {
  switch (*opchar) {
  case 'e':
    options->eflag = 1;
    Ecase(options->strPattern, optarg);
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
    Fcase(options);
    break;
  case 'o':
    options->oflag = 1;
    break;
  default:
    printf("usage: grep [-benstuv] [file ...]\n");
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
//       regFound = regexec(&regex, strStr, 0, NULL, registflag);
//       if (regFound == opposflag){
//         success++;
//       }
//       if ((regFound == opposflag) && options.lflag) {//печать только имени
//       файла
//         printf("%s", argv[currfile]);
//       }
//       if ((regFound == opposflag) && fnameflag && !options.lflag &&
//       !options.cflag && !options.oflag) {//печать с именем файла
//         printf("%s:", argv[currfile]);
//         if (options.nflag) {
//           printf("%d:", countStr);
//         }
//         printf("%s", strStr);
//       }
//       if ((regFound == opposflag) && !fnameflag && !options.lflag &&
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