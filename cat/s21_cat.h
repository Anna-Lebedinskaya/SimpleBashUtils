#include <getopt.h>
#include <stdio.h>
// #include <stdlib.h>
// #include <string.h>

typedef struct cat_flag {
  int s;  //сжимает несколько смежных пустых строк
  int b;  //нумерует только непустые строки
  int n;  //нумерует все выходные строки
  int e;  //-e предполагает и -v, отображает символы конца строки как $
  int t;  //-t предполагает и -v, отображает табы как ^I
  int v;  //отображает непечатаемые символы
  //  E;  //то же самое -e, но без применения -v
  //  T;  //то же самое -t, но без применения -v
} Cat_opt;

int pars(int argc, char* argv[], Cat_opt* flag);
int get_size_file(char* file_name);
void print(Cat_opt flag, FILE* file_name, int size_file);
