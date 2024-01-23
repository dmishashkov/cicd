#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#define chunkSize 1024

#ifndef _UTILS_H
#define _UTILS_H

void numerate_strings(char *string, long long int *counter, int flag);

void replace_symbol_with_string(char *string, char *replace, char **with,
                                int flag, int len);

void delete_empty(char *cur, char *prev, int *curF, int *prevF);

int check_for_existance(FILE *file);

void display_file_content(FILE *file);

int read_string(FILE *file, char *string, int alwaysAddNewLine);

int is_empty_string(char *string);

int is_empty_file(FILE *file);

int is_null_string(char *string);

int generatePatterns(regex_t *compiledPatterns, char **patterns,
                     int patternsLen, int iflag);

int count_substring(FILE *file, char *pattern);

int getRegexFromFile(char *fileName, char **patterns, int *counter);

void executeFullRegex(regex_t pattern, char *string, char **matchedSubStrings,
                      int *matchedSubStringsNumber);
void outputFullSubstrings(char **matchedSubStrings, int count, int hflag,
                          int nflag, int fileCount, int currentLineNumber,
                          char *fileName);
#endif
