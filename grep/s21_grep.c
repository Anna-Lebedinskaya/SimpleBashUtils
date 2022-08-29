#include "s21_grep.h"

void pars(int argc, char* argv[], grep_flags* data) {
  int rez = 0, j = 0;
  while ((rez = getopt(argc, argv, "e:ivclnhsf:o")) != -1) {
    if (rez == 'e')
      data->flag[1]++, data->p_search_string[j++] = optarg;
    else if (rez == 'f')
      data->flag[9]++;  // todo: open file
    else if (rez == 'i')
      data->flag[2]++;
    else if (rez == 'v')
      data->flag[3]++;
    else if (rez == 'c')
      data->flag[4]++;
    else if (rez == 'l')
      data->flag[5]++;
    else if (rez == 'n')
      data->flag[6]++;
    else if (rez == 'h')
      data->flag[7]++;
    else if (rez == 's')
      data->flag[8]++;
    else if (rez == 'o')
      data->flag[10]++;
  }
  // argc = argc - optind;
  // argv += optind;
  int pos = optind;

  if (!data->flag[1]) {
    data->p_search_string[0] = argv[pos];
    for (int i = 0; i < argc - 1 - pos; i++) {
      data->p_file_name[i] = argv[pos + i + 1];
    }
  } else {
    for (int i = 0; i < argc - pos; i++) {
      data->p_file_name[i] = argv[pos + i];
    }
  }
}

void print(grep_flags* data) {
  int regflag = REG_EXTENDED;
  if (data->flag[2]) regflag = REG_ICASE;
  int compare = 0;
  if (data->flag[3]) compare = REG_NOMATCH;
  regex_t regex;

  for (int i = 0; data->p_search_string[i]; i++) {
    if (regcomp(&regex, data->p_search_string[i], regflag) == 0) {
      for (int j = 0; data->p_file_name[j]; j++) {
        FILE* file = fopen(data->p_file_name[j], "r");
        if (file) {
          char line[1000] = {0};
          int success = 0;
          int str_count = 0;
          int comp_count = 0;
          while (!feof(file)) {
            if (fgets(line, 1000, file) != NULL) {
              str_count++;

              success = regexec(&regex, line, 0, NULL, 0);
              if (success == compare) {
                if (data->flag[4]) {
                  comp_count++;
                  if (data->flag[5]) break;
                  continue;
                }
                if (data->flag[5]) {
                  printf("%s\n", data->p_file_name[j]);
                  break;
                }
                if ((data->p_file_name[1]) && (data->flag[7] == 0))  //???
                  printf("%s:", data->p_file_name[j]);
                if (data->flag[6]) printf("%d:", str_count);
                printf("%s", line);
              }
              memset(line, 0, 1000);
            }
          }
          if (data->flag[4]) {
            if (data->p_file_name[1] && data->flag[7] == 0) {
              printf("%s:", data->p_file_name[j]);
            }
            printf("%d\n", comp_count);
            if (data->flag[5]) printf("%s\n", data->p_file_name[j]);
          }
          fclose(file);
        } else {
          if (data->flag[8] == 0)
            fprintf(stderr, "No such file or directory\n");
        }
      }
    } else {
      fprintf(stderr, "No such expression\n");
    }
  }
  regfree(&regex);
}

int main(int argc, char* argv[]) {
  if (argc > 1) {
    grep_flags data = {{0}, {0}, {0}};
    pars(argc, argv, &data);
    print(&data);
  }
  return 0;
}
