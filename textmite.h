
#ifndef TEXTMITELIB_H
#define TEXTMITELIB_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h> //good. perfect
void printfile(FILE *file);
void double_check(int suspect);
void error_handler(void *argument, int fatal);
FILE *open_file(char filename[], int file_type);
void help_panel(void);
void del_line(char *filename, char *arr_of_input[]);
void ins_line(char *filename, char *arr_of_input[]);
#endif // TEXTMITELIB_H