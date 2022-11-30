#include "s21_grep.h"

// valgrind
// cppcheck
//убрать fsanetize
//-fsanitize=address
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
  if (!options.hflag) {
    Filename(&options, optind);
  }
  decrement_for_EF(&find, options);
  strcat(options.strSearch, argv[find]);
  if_E_or_F(options, options.strPattern, options.strSearch);

  while (find < (argc)) {
    int Nullflag = 0;
    FILE *fp = NULL;
    File_range(options, &Nullflag, find, &fp);
    options.CFlagcount = 0;

    while (!Nullflag &&
           ((options.gline = getline(&(options.strStr), &sizeStr, fp)) != -1)) {
      memset(options.strBuf, 0, 1024);
      FileString_format(&options);
      options.Ncount += 1;
      int success = 0;
      if (options.iflag) {
        registflag = REG_NEWLINE | REG_EXTENDED | REG_ICASE;
      }
      Vflag(&options, &success);
      regcomp(&regex, options.strSearch, registflag);

      if (options.oflag && !options.vflag) { //-------------------------o
        int line_pos = 0;
        int length = strlen(options.strStr);

        options.regFound = regexec(&regex, options.strStr, 1, pmatch, 0);
        if (options.regFound == success) {
          options.CFlagcount++;
        }

        while (regexec(&regex, options.strStr + line_pos, 1, pmatch, 0) ==
               success) {
          N_Fname_comb(&options, find);
          int k = strlen(options.strBuf);
          for (int i = pmatch->rm_so; i < pmatch->rm_eo; i++) {
            (options.strBuf)[k] = (options.strStr + line_pos)[i];
            k++;
          }
          (options.strBuf)[strlen(options.strBuf)] = '\n';
          
          line_pos = line_pos + pmatch->rm_eo;
          if (pmatch->rm_eo == pmatch->rm_so)
            line_pos++;
          if (line_pos > length) {
            break;
          }
        }
      } else {
        options.regFound = regexec(&regex, options.strStr, 1, pmatch, 0);
        if (options.regFound == success) {
          options.CFlagcount++;
          N_Fname_comb(&options, find);
          strcat(options.strBuf, options.strStr);
        }
      }
      if (!options.cflag && !options.lflag && (options.regFound == success)) {
        printf("%s", options.strBuf);
      }
      regfree(&regex);
    }
    if (options.cflag) {

 if (options.lflag && options.CFlagcount > 0){
  options.CFlagcount=1;
 }

      if ((find + 1) < argc) {
        if (options.FilenameFlag) {
          sprintf(options.strBuf, "%s:%d", (options.argv)[find + 1],
                  options.CFlagcount);
        } else {
          sprintf(options.strBuf, "%d", options.CFlagcount);
        }
        printf("%s\n", options.strBuf);
      }
    }

    if (options.lflag && options.CFlagcount > 0) {
      strcpy(options.strBuf, (options.argv)[1 + find]);
      strcat(options.strBuf, "\n");
      printf("%s", options.strBuf);
    }
    options.Ncount = 0;
    if (fp != NULL) {
      fclose(fp);
    }
    find++;
  }
  free_at_exit(&options);
  return flag;
}

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
void N_Fname_comb(opt *options, int find) {
  if (options->FilenameFlag && options->nflag) {
    sprintf(options->strBuf, "%s:%d:", (options->argv)[find + 1],
            options->Ncount);
  } else {
    if (options->FilenameFlag && !options->nflag) {
      sprintf(options->strBuf, "%s:", (options->argv)[find + 1]);
    } else {
      if (!(options->FilenameFlag) && options->nflag) {
        sprintf(options->strBuf, "%d:", options->Ncount);
      }
    }
  }
}
void Filename(opt *options, int nefl) {
  // if ((options->eflag || options->fflag)&& ((options->argc)-nefl>=2)){
  //   options->FilenameFlag=1;
  // }
  //   else {
  //   if ((options->argc-nefl!=2)){
  //   options->FilenameFlag=1;
  // }
  // }
  if ((options->eflag || options->fflag) &&
      (options->argc - options->Argcount > 2)) {
    options->FilenameFlag = 1;
  } else {
    if (options->argc - options->Argcount > 3) {
      options->FilenameFlag = 1;
    }
  }
}
void FileString_format(opt *options) {
  int len = strlen((options->strStr));
  if ((options->strStr)[len - 1] != '\n') {
    strcat((options->strStr), "\n");
  }
}
void Vflag(opt *options, int *success) {
  if (options->vflag) {
    *success = REG_NOMATCH;
  }
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
    options->Argcount += 2;
    Ecase(options->strPattern, optarg);
    break;
  case 'i':
    options->iflag = 1;
    options->Argcount++;
    break;
  case 'v':
    options->vflag = 1;
    options->Argcount++;
    break;
  case 'c':
    options->cflag = 1;
    options->Argcount++;
    break;
  case 'l':
    options->lflag = 1;
    options->Argcount++;
    break;
  case 'n':
    options->nflag = 1;
    options->Argcount++;
    break;
  case 'h':
    options->hflag = 1;
    options->Argcount++;
    break;
  case 's':
    options->sflag = 1;
    options->Argcount++;
    break;
  case 'f':
    options->fflag = 1;
    options->Argcount += 2;
    Fcase(options);
    break;
  case 'o':
    options->oflag = 1;
    options->Argcount++;
    break;
  default:
    printf("usage: grep [-benstuv] [file ...]\n");
  }
}
