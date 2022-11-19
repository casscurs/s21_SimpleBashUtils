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

//void ifflag(int *cur, int *prev, int *i, int *empt, opt options);
void argc_check(int argc,int* flag);
void flag_turn(int argc, char **argv, opt *options,char* strPattern, int* flag);
void file_check(char *str, int *Nullflag, FILE **fp);
void malloc_check(char **strStr,int* flag);
void last_sym_rewrite(char* strPattern);
void decrement_optind(int* find,opt options);
void if_E_or_F(opt options,char* strPattern,char* strSearch);
void Ecase(char* strPattern,char* str);
void Fcase(int* flag,char* strPattern);
void switchcase(int *opchar,char *strPattern,opt *options,int *flag);
//void mainwork(int argc, char **argv, int *currfile, opt options);

#endif