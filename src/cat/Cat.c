
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
  int flag = 0;
  int opt;
  FILE *fp = NULL;
  int b = 0;
  int opchar = 0;
  int opindex = 0;

  struct option opts[] = {
      {"squeeze-blank", no_argument, 0, 's'},
      {"number-nonblank", no_argument, 0, 'b'},
      {"E", no_argument, 0, 'e'},
      {"number", no_argument, 0, 'n'},
      {"T", no_argument, 0, 't'},
      {"v", no_argument, 0, 'v'},
      {0, 0, 0, 0},
  };

  while (-1 != (opchar = getopt_long(argc, argv, "+sbentv", opts, &opindex))) {
    switch (opchar) {
    case 'b':
      options.bflag = 1;
      break;
    case 'e':
      options.eflag = 1;
      options.vflag = 1;
      break;
    case 'n':
      options.nflag = 1;
      break;
    case 's':
      options.sflag = 1;
      break;
    case 't':
      options.tflag = 1;
      options.vflag = 1;
      break;
    case 'E':
      options.eflag = 1;
      break;
    case 'T':
      options.tflag = 1;
      break;
    case 'v':
      options.vflag = 1;
      break;
    default:
      printf("usage: cat [-benstuv] [file ...]\n");
    }
  }
  int currfile = optind;
  int currempt = 0;
  int lastempt = 0;
  int empt = 0;
  int cur;
  int Deleteflag = 0;
  int prev = '\n';
  int i = 1;

  while (currfile <= argc) {
    if (currfile != argc) {
      fp = fopen(argv[currfile], "r");
      if (fp == NULL) {
        printf("cat: %s: No such file or directory\n", argv[currfile]);
        flag = 1;
        break;
        // currfile++;
        // continue;
      }
    }
    while ((cur = fgetc(fp)) != EOF) {
      if (options.sflag && (cur == '\n') && (prev == '\n')) {
        empt++;
        if (empt > 1) {
          Deleteflag = 1;
        }
      } else {
        Deleteflag = 0;
        empt = 0;
      }

      if (!Deleteflag) {
        if (((options.nflag && !options.bflag) ||
             (options.bflag && cur != '\n')) &&
            (prev == '\n')) {
          printf("%*d\t", 6, i);
          i++;
        }
      
      if (options.tflag && cur == '\t') {
        printf("^");
        cur = 'I';
      }

      if (options.eflag && cur == '\n') {
        printf("$");
      }
      if (options.vflag) {
        while (cur >= 128) {
          cur = cur - 128;
        }
        if (((cur < 9) && (cur >= 0)) || ((cur > 10) && (cur < 32))) {
          printf("^");
          cur = cur + 64;
        } else if (cur == 127) {
          printf("^");
          cur = '?';
        }
      }
      putchar(cur);
      prev = cur;
      }
    }
    fclose(fp);
    currfile++;
  }
  return flag;
}