#include "s21_cat.h"

int main(int argc, char **argv) {
  int flag = 0;
  opt options = {0};
  flag_turn(argc, argv, &options);
  int currfile = optind;
  mainwork(argc, argv,&currfile,options);
  return flag;
}
void mainwork(int argc, char **argv,int* currfile,opt options){
  int Nullflag = 0;
  FILE *fp = NULL;
  int cur;
  int prev = '\n';
    int i = 1;
  int empt = 0;
  while (*currfile <= argc) {
        if (*currfile != argc) {
      fp = fopen(argv[*currfile], "r");
      if (fp == NULL) {
        printf("\ncat: %s: No such file\n", argv[*currfile]);
        Nullflag = 1;
        (*currfile)++;
        continue;
      } else {
        Nullflag = 0;
      }
    }
    while (!Nullflag && ((cur = fgetc(fp)) != EOF)) {
      ifflag(&cur, &prev, &i,&empt, options);
    }
    fclose(fp);
    (*currfile)++;
  }
}
void ifflag(int *cur, int *prev, int *i,int* empt, opt options) {
  int Deleteflag = 0;
  if (options.sflag && (*cur == '\n') && (*prev == '\n')) {
    (*empt)++;
    if (*empt > 1) {
      Deleteflag = 1;
    }
  } else {
    Deleteflag = 0;
    *empt = 0;
  }
  if (!Deleteflag) {
    if (((options.nflag && !options.bflag) ||
         (options.bflag && (*cur != '\n'))) &&
        (*prev == '\n')) {
      printf("%*d\t", 6, *i);
      (*i)++;
    }
    if (options.tflag && (*cur == '\t')) {
      printf("^");
      *cur = 'I';
    }
    if (options.eflag && (*cur == '\n')) {
      printf("$");
    }
    if (options.vflag) {
      while (*cur >= 128) {
        *cur = *cur - 128;
      }
      if (((*cur < 9) && (*cur >= 0)) || ((*cur > 10) && (*cur < 32))) {
        printf("^");
        *cur = *cur + 64;
      } else if (*cur == 127) {
        printf("^");
        *cur = '?';
      }
    }
    putchar(*cur);
    *prev = *cur;
  }
}
void flag_turn(int argc, char **argv, opt *options) {
  int opchar = 0;
  int opindex = 0;
  while (-1 != (opchar = getopt_long(argc, argv, "+sbentv", opts, &opindex))) {
    switch (opchar) {
    case 'b':
      options->bflag = 1;
      break;
    case 'e':
      options->eflag = 1;
      options->vflag = 1;
      break;
    case 'n':
      options->nflag = 1;
      break;
    case 's':
      options->sflag = 1;
      break;
    case 't':
      options->tflag = 1;
      options->vflag = 1;
      break;
    case 'E':
      options->eflag = 1;
      break;
    case 'T':
      options->tflag = 1;
      break;
    case 'v':
      options->vflag = 1;
      break;
    default:
      printf("usage: cat [-benstuv] [file ...]\n");
    }
  }
}