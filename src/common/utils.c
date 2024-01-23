#include "utils.h"

#include <regex.h>
#include <string.h>

void numerate_strings(char *string, long long int *counter, int flag) {
  if (flag) {
    if (!is_null_string(string)) {
      if (!is_empty_string(string)) {
        printf("%6lld\t", *counter);
        (*counter)++;
      }
    }
  } else {
    if (!is_null_string(string)) {
      printf("%6lld\t", *counter);
      (*counter)++;
    }
  }
}

int check_for_existance(FILE *file) {
  int res = 0;
  if (file == NULL) {
    res = 1;
  } else {
    res = 0;
  }
  return res;
}

void display_file_content(FILE *file) {
  while (!feof(file)) {
    char string[2048];
    read_string(file, string, 0);
    printf("%s", string);
  }
}

int read_string(FILE *file, char *string, int alwaysAddNewLine) {
  int counter = 0;
  int c;
  while (((c = fgetc(file)) != EOF)) {
    if (c == '\n') {  // переписать
      string[counter] = '\n';
      counter++;
      break;
    }
    string[counter] = c;
    counter++;
  }
  if (c == EOF && alwaysAddNewLine && counter != 0) {
    string[counter] = '\n';
    counter++;
  }
  string[counter] = '\0';
  return counter;
}

int is_empty_string(char *string) {
  int res = 0;
  if (string[0] == '\n') {
    res = 1;
  } else {
    res = 0;
  }
  return res;
}

int is_null_string(char *string) {
  int res = 0;
  if (string[0] == '\0') {
    res = 1;
  } else {
    res = 0;
  }
  return res;
}

int is_empty_file(FILE *file) {
  int result;
  fseek(file, 0, SEEK_END);
  int size = ftell(file);

  if (size == 0) {
    result = 1;
  } else {
    result = 0;
  }
  return result;
}

void replace_symbol_with_string(char *string, char *replace, char **with,
                                int flag, int len) {
  int strlength = strlen(string);
  char m_notation[] = "@ABCDEFGH**KLMNOPQRSTUVWXYZ[\\]^_";
  for (int i = 0; i < strlength; i++) {
    int replaced = 0;
    int c = (int)string[i];
    for (int j = 0; j < len; j++) {
      if (c == (int)replace[j]) {
        printf("%s", with[j]);
        replaced = 1;
      }
    }
    if (!replaced) {
      if (flag) {
        if ((c <= 31 && c != 10 && c != 9) || c == 127) {
          if (c <= 31) {
            printf("^%c", m_notation[c]);
          } else {
            printf("^?");
          }
        } else {
          putchar(c);
        }
      } else {
        putchar(c);
      }
    }
  }
}

int generatePatterns(regex_t *compiledPatterns, char **patterns,
                     int patternsLen, int iflag) {
  int code = 0;
  int flag = 0;
  if (iflag) {
    flag = REG_ICASE;
  }
  for (int i = 0; i < patternsLen; i++) {
    regex_t regex;
    code = regcomp(&regex, patterns[i],
                   REG_NEWLINE | flag);  // сделать обработку ошибок
    compiledPatterns[i] = regex;
  }
  return code;
}
int getRegexFromFile(char *fileName, char **patterns, int *counter) {
  int res = 0;
  FILE *file = fopen(fileName, "rb");
  if (file != NULL) {
    while (!feof(file)) {
      char currentString[2048] = {0};
      int len = read_string(file, currentString, 1);
      if (!is_null_string(currentString)) {
        currentString[len - 1] = '\0';
        currentString[len] = '0';
      }
      strcpy(patterns[*counter], currentString);
      (*counter)++;
    }
    fclose(file);
  } else {
    res = -1;
  }
  return res;
}

void executeFullRegex(regex_t pattern, char *string, char **matchedSubStrings,
                      int *matchedSubStringsNumber) {
  size_t nmatch = 2;
  regmatch_t pmatch[2];
  int code = 1;
  while ((code = regexec(&pattern, string, nmatch, pmatch, 0)) != 1) {
    strncpy(matchedSubStrings[*matchedSubStringsNumber],
            &string[pmatch[0].rm_so], pmatch[0].rm_eo - pmatch[0].rm_so);
    string = string + pmatch[0].rm_eo;
    (*matchedSubStringsNumber)++;
  }
}

void outputFullSubstrings(char **matchedSubStrings, int count, int hflag,
                          int nflag, int fileCount, int currentLineNumber,
                          char *fileName) {
  for (int i = 0; i < count; i++) {
    if (!hflag && fileCount >= 2) {
      printf("%s:", fileName);
    }
    if (nflag) {
      printf("%d:", currentLineNumber);
    }
    printf("%s\n", matchedSubStrings[i]);
  }
}