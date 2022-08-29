#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <string.h>

typedef struct grep_flags {
  int flag[10];  // 1-e, 2-i, 3-v, 4-c, 5-l, 6-n, 7-h, 8-s, 9-f, 0-o
  char* p_search_string[100];
  char* p_file_name[100];
} grep_flags;

void pars(int argc, char* argv[], grep_flags* data);
void print(grep_flags* data);
