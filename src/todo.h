#ifndef TODO_H
#define TODO_H

const char *FILE_NAME = ".todo";

void add_todo(char *text, int priority);
void remove_todo(int index);
void print_todo();
void done(int index);

#endif
