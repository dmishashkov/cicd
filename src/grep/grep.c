#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "../common/utils.h"

int main(int argc, char **argv) {
  FILE *file = NULL;
  int res, oflag = 0, sflag = 0, hflag = 0, eflag = 0, iflag = 0, vflag = 0,
           cflag = 0, lflag = 0, nflag = 0, fflag = 0, patternsLength = 0;
  char **patternsArray;
  regex_t *regularExpressions = (regex_t *)calloc(128, sizeof(regex_t));
  patternsArray = (char **)calloc(128, sizeof(char *));
  for (int i = 0; i < 128; i++) {
    patternsArray[i] = (char *)calloc(1028, sizeof(char));
  }
  char **matchedSubStrings = (char **)calloc(256, sizeof(char *));
  for (int i = 0; i < 256; i++) {
    matchedSubStrings[i] = (char *)calloc(256, sizeof(char));
  }
  while ((res = getopt(argc, argv, "e:ivclnhsof:")) != -1) {
    switch (res) {
      case 'e':
        strcpy(patternsArray[patternsLength], optarg);
        patternsLength++;
        eflag++;
        break;
      case 'i':
        iflag++;
        break;
      case 'v':
        vflag++;
        break;
      case 'c':
        cflag++;
        break;
      case 'l':
        lflag++;
        break;
      case 'n':
        nflag++;
        break;
      case 'h':
        hflag++;
        break;
      case 'o':
        oflag++;
        break;
      case 's':
        sflag++;
        break;
      case 'f':
        getRegexFromFile(optarg, patternsArray, &patternsLength);
        fflag++;
      default:

        break;
    }
  }
  if (!eflag && !fflag) {
    strcpy(patternsArray[0], argv[optind]);
    optind++;
    patternsLength = 1;
  }
  generatePatterns(regularExpressions, patternsArray, patternsLength, iflag);
  int filesIter, filesCount;
  filesCount = argc - optind;
  for (filesIter = optind; filesIter < argc; filesIter++) {
    file = fopen(argv[filesIter], "rb");
    if (file != NULL) {
      int currentLineNumber = 1, matchedLinesCount = 0, isMatchedFile = 0;
      while (!feof(file)) {
        char currentLine[2048];
        read_string(file, currentLine, 1);
        int isNull = 0;
        isNull = is_null_string(currentLine);
        if (!isNull) {
          int matched = 0;
          for (int i = 0; i < patternsLength; i++) {
            int code = 0;
            code = regexec(&(regularExpressions[i]), currentLine, 0, NULL, 0);
            if (!cflag && !lflag && !(oflag && vflag)) {
              if (!code && !matched && !vflag) {
                if (!oflag && !cflag && !lflag) {
                  if (filesCount >= 2 && !hflag) {
                    printf("%s:", argv[filesIter]);
                  }
                  if (nflag) {
                    printf("%d:", currentLineNumber);
                  }
                  printf("%s", currentLine);
                } else {
                  int num = 0;
                  executeFullRegex(regularExpressions[i], currentLine,
                                   matchedSubStrings, &num);
                  outputFullSubstrings(matchedSubStrings, num, hflag, nflag,
                                       filesCount, currentLineNumber,
                                       argv[filesIter]);
                  for (i = 0; i < 256; i++) {
                    memset(matchedSubStrings[i], '\0', sizeof(char) * 256);
                  }
                }
              }
            }
            if (code == 0 && !matched) {
              matched = 1;
            }
          }
          if (matched && !vflag) {
            isMatchedFile = 1;
            matchedLinesCount++;
          }
          if (!matched && vflag) {
            if (!cflag && !lflag && !oflag) {
              if (filesCount >= 2 && !hflag) {
                printf("%s:", argv[filesIter]);
              }
              if (nflag) {
                printf("%d:", currentLineNumber);
              }
              printf("%s", currentLine);
            }
            isMatchedFile = 1;
            matchedLinesCount++;
          }
          currentLineNumber++;
        }
      }

      if (lflag && isMatchedFile) {
        printf("%s\n", argv[filesIter]);
      } else if (cflag && !lflag) {
        if (filesCount >= 2 && !hflag) {
          printf("%s:", argv[filesIter]);
        }
        printf("%d\n", matchedLinesCount);
      }
      fclose(file);
    } else {
      fprintf(stderr, "Error opening file with name: %s\n", argv[filesIter]);
    }
  }
  for (int i = 0; i < 128; i++) {
    free(patternsArray[i]);
  }
  free(patternsArray);
  for (int i = 0; i < patternsLength; i++) {
    regfree(&regularExpressions[i]);
  }
  free(regularExpressions);
  for (int i = 0; i < 256; i++) {
    free(matchedSubStrings[i]);
  }
  free(matchedSubStrings);
  return 0;
}
