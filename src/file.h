#pragma once
#include <stdio.h>

char *get_dir();
char *get_file_name();

void create_folder();
void create_file();

FILE *get_file(char *mode);
void append_data(char *data);
