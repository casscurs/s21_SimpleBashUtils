#ifndef S21_GREP_H
#define S21_GREP_H

#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define sizeSearch 4096

typedef struct options {
  int eflag;
  int iflag;
  int vflag;
  int cflag;
  int lflag;
  int nflag;
  int hflag;
  int sflag;
  int fflag;
  int oflag;
  
  char *strStr;
  char *strFile;

  char strSearch[sizeSearch];
  char strPattern[sizeSearch];
  int argc;
  char **argv;
  int gline;
  int regFound;
  //добавить основные переменные
} opt;

struct option opts[] = {
    {"regexp", no_argument, 0, 'e'},
    {"ignore-case", no_argument, 0, 'i'},
    {"invert-match", no_argument, 0, 'v'},
    {"count", no_argument, 0, 'c'},
    {"files-with-matches", no_argument, 0, 'l'},
    {"line-number", no_argument, 0, 'n'},
    {"no-filename", no_argument, 0, 'h'},
    {"no-messages", no_argument, 0, 's'},
    {"file", no_argument, 0, 'f'},
    {"only-matching", no_argument, 0, 'o'},
    {0, 0, 0, 0},
};

void argc_check(opt *options);
void pars_and_prework(opt *options);
void file_check(char *str, int *Nullflag, FILE **fp);
void malloc_check(char* str,opt *options);
void last_sym_rewrite(char* strPattern);
void decrement_for_EF(int* find,opt options);
void if_E_or_F(opt options,char* strPattern,char* strSearch);
void Ecase(char* strPattern,char* str);
void Fcase(opt *options);
void switchcase(int *opchar, opt *options);
void file_check_exit(char *str, int *Nullflag, FILE **fp,opt *options);

#endif