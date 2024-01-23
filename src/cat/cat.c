#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "../common/utils.h"

static int bflag, eflag, nflag, sflag, tflag, vflag, Tflag, Eflag;
int main(int argc, char **argv) {
  // int bflag, eflag, nflag, sflag, tflag, vflag;
  int res = 0, currentLineEmpty = 0, prevLineEmpty = 0, replaceCharsLen = 0,
      optionIndex = 0;
  char replaceChars[64] = {0};
  char **replaceStrings = NULL;
  replaceStrings = (char **)malloc(128 * sizeof(char *));
  for (int i = 0; i < 128; i++) {
    replaceStrings[i] = (char *)malloc(1028 * sizeof(char));
  }
  long long int counter = 1;
  FILE *file = NULL;
  static struct option long_options[] = {
      {"number-nonblank", no_argument, &bflag, 1},
      {"number", no_argument, &nflag, 1},
      {"squeeze-blank", no_argument, &sflag, 1}};
  while ((res = getopt_long(argc, argv, "benstvET", long_options,
                            &optionIndex)) != -1) {
    switch (res) {
      case 'b':
        bflag++;
        break;
      case 'e':
        if (eflag == 0) {
          replaceChars[replaceCharsLen] = '\n';
          strcpy(replaceStrings[replaceCharsLen], "$\n");
          replaceCharsLen++;
        }
        eflag++;
        break;
      case 'n':
        nflag++;
        break;
      case 's':
        sflag++;
        break;
      case 't':
        if (tflag == 0) {
          replaceChars[replaceCharsLen] = '\t';
          strcpy(replaceStrings[replaceCharsLen], "^I");
          replaceCharsLen++;
        }
        tflag++;
        break;
      case 'v':
        vflag++;
        break;
      case 'T':
        if (Tflag == 0) {
          replaceChars[replaceCharsLen] = '\t';
          strcpy(replaceStrings[replaceCharsLen], "^I");
          replaceCharsLen++;
        }
        Tflag++;
        break;
      case 'E':
        if (Eflag == 0) {
          replaceChars[replaceCharsLen] = '\n';
          strcpy(replaceStrings[replaceCharsLen], "$\n");
          replaceCharsLen++;
        }
        Eflag++;
        break;
    }
  }
  for (int filesIter = optind; filesIter < argc; filesIter++) {
    file = fopen(argv[filesIter], "rb");
    if (file != NULL) {
      while (!feof(file)) {
        char currentLine[2048];
        prevLineEmpty = currentLineEmpty;
        read_string(file, currentLine, 0);
        if (sflag) {
          prevLineEmpty = currentLineEmpty;
          currentLineEmpty = is_empty_string(currentLine);
        }
        if (!currentLineEmpty || !prevLineEmpty) {
          if (bflag) {
            numerate_strings(currentLine, &counter, 1);
          } else if (nflag) {
            numerate_strings(currentLine, &counter, 0);
          }
          if (eflag || tflag) {
            replace_symbol_with_string(currentLine, replaceChars,
                                       replaceStrings, 1, replaceCharsLen);
          }
          if (vflag && !eflag && !tflag) {
            replace_symbol_with_string(currentLine, replaceChars,
                                       replaceStrings, 1, replaceCharsLen);
          }
          if (vflag && Tflag && Eflag) {
            replace_symbol_with_string(currentLine, replaceChars,
                                       replaceStrings, 1, replaceCharsLen);
          }
          if (!eflag && !tflag && !vflag) {
            printf("%s", currentLine);
          }
        }
      }
      fclose(file);
    } else {
      fprintf(stderr, "File does not exist\n");
    }
  }
  for (int i = 0; i < 128; i++) {
    free(replaceStrings[i]);
  }
  free(replaceStrings);
  return 0;
}
