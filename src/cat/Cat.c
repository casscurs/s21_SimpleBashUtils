#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
int main(int argc, char **argv) {
  int length;
  int flag = 0, bflag = 0, eflag = 0, nflag = 0, sflag = 0;
  int opt;
  FILE *fp=NULL;
  //блок getline
  int b_read;
  size_t size = 10;
  char *str;
  //
  while ((opt = getopt(argc, argv, "bens")) != -1) {
    switch (opt) {
    case 'b':
      bflag = 1;
      break;
    case 'e':
      eflag = 1;
      break;
    case 'n':
      nflag = 1;
      break;
    case 's':
      sflag = 1;
      break;
    }
  }
  int currfile = optind;
  str = (char *)malloc(size);
  while (currfile <= argc) {
    if (currfile != argc) {
      fp = fopen(argv[currfile], "rb");
      if (fp == NULL) {
        printf("No such file or directory");
        flag = 1;
      }
    }
    int lastempt = 0;

    while ((getline(&str, &size, (fp == NULL ? stdin : fp))) != -1) {
      length = strlen(str);
      str[length - 1] = '\0';
      //fprintf(stdout, "%s\n", str);
    }
    fclose(fp);
    currfile++;
  }
  free(str);
  return flag;
}