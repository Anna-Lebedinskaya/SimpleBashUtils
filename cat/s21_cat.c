#include "s21_cat.h"

int pars(int argc, char* argv[], Cat_opt* flag) {
  const char* short_options = "benstvET";

  const struct option long_options[] = {
      {"--number-nonblank", no_argument, NULL, 'b'},
      {"--number", no_argument, NULL, 'n'},
      {"--squeeze-blank", no_argument, NULL, 's'},
      {NULL, 0, NULL, 0}};

  int rez = 0;
  while ((rez = getopt_long(argc, argv, short_options, long_options, NULL)) !=
         -1) {
    switch (rez) {
      case 'b':
        flag->b = 1;
        break;

      case 'e':
        flag->e = 1;
        flag->v = 1;
        break;

      case 'n':
        flag->n = 1;
        break;

      case 's':
        flag->s = 1;
        break;

      case 't':
        flag->t = 1;
        flag->v = 1;
        break;

      case 'v':
        flag->v = 1;
        break;

      case 'E':
        flag->e = 1;
        break;

      case 'T':
        flag->t = 1;
        break;
    }
  }
  // *argc = *argc - optind;
  // *argv += optind;
  return optind;
}

int get_size_file(char* file_name) {
  int size_file = 0;
  FILE* file_rb = fopen(file_name, "rb");
  if (file_rb != NULL) {
    fseek(file_rb, 0, SEEK_END);
    size_file = (int)ftell(file_rb);
    fclose(file_rb);
  }
  return size_file;
}

void print(Cat_opt flag, FILE* file_name, int size_file) {
  int size_file_start = size_file;
  int number = 1;
  char ch = 0;
  char last_ch = 0;

  if (size_file > 0) {
    while (size_file--) {
      last_ch = ch;
      ch = fgetc(file_name);

      if (flag.s) {
        if ((ch == '\n') &&
            ((last_ch == '\n') || (size_file == size_file_start - 1))) {
          flag.s++;
        } else if ((ch == '\n') && (flag.s >= 3)) {
          flag.s++;
        } else {
          flag.s = 1;
        }
        if (flag.s >= 3) continue;
      }

      if (flag.b) {
        if ((size_file == size_file_start - 1) && (ch != '\n')) {
          printf("%6d\t", number);
          number++;
          flag.b++;
        } else if (ch == '\n') {
          flag.b = 1;
        } else if ((ch != '\n') && (flag.b == 1)) {
          printf("%6d\t", number);
          number++;
          flag.b++;
        }
      } else if (flag.n) {
        if (flag.n == 1) {
          printf("%6d\t", number++);
          flag.n++;
        }
        if (ch == '\n') {
          flag.n = 1;
        }
      }

      if (flag.e == 1) {
        if (ch == '\n') {
          printf("$");
        }
      }

      if (flag.t) {
        if (ch == '\t') {
          printf("^I");
          continue;
        }
      }

      if (flag.v) {
        if (((ch >= 0) && (ch <= 8)) || ((ch >= 11) && (ch <= 31))) {
          printf("^%c", ch + 64);
          continue;
        } else if (ch == 127) {
          printf("^?");
          continue;
        } else if (ch <= -97) {
          printf("M-^%c", ch - 64);
          continue;
        }
      }

      printf("%c", ch);
    }
  }
}

int main(int argc, char* argv[]) {
  if (argc > 1) {
    Cat_opt flag = {0, 0, 0, 0, 0, 0};
    int pos = pars(argc, argv, &flag);
    for (int i = pos; i < argc; i++) {
      int size_file = 0;
      size_file = get_size_file(argv[i]);
      FILE* file_r = fopen(argv[i], "r");

      if (file_r != NULL) {
        print(flag, file_r, size_file);
        fclose(file_r);
      }
    }
  } else {
    fprintf(stderr, "a few arguments");
  }
  return 0;
}
