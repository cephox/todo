#include "todo.h"

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

void print_help(char *name) {
	printf("Todo:\n-----------------------------------\nTodo is a cli to manage your todo list\n\nSyntax:\n%s add \"Thing to do\" [Priority (default: 1)]\n%s remove 0\n\nAuthor: ce_phox\n", name, name);
}

int main(int argc, char *argv[]) {

	if(argc == 1) {
		if(access(FILE_NAME, F_OK) != -1) {
			print_todo();
			return 0;
		}
	}

	if(argc < 3) {
		print_help(argv[0]);
		return 0;
	}

	if(strcmp(argv[1], "add") == 0) {
		if(argc == 4)
			add_todo(argv[2], atoi(argv[3]));
		else
			add_todo(argv[2], 1);
	} else if(strcmp(argv[1], "remove") == 0) {
		remove_todo(atoi(argv[2]));
	}

	return 0;
}

void print_todo() {

	printf("Index | Done | Priority | Thing to do\n");

	FILE *file = fopen(FILE_NAME, "r");

	char *line = NULL;
	size_t len = 0;
	ssize_t read;

	int index = 1;

	while((read = getline(&line, &len, file) != -1)) {

		char *current = strtok(line, "|");
		int i = 0;

		int priority = 1;
		int done = 0;
		char *todo;
		while(current != NULL) {

			if(i == 0) {
				done = atoi(current);
			} else if(i == 1) {
				priority = atoi(current);
			} else if(i == 2) {
				break;
			}
			i++;
			current = strtok(NULL, "|");
		}
		strtok(current, "\n");

		char *d = done ? "Yes" : "No";

		printf("%-8i%-7s%-11i%s\n", index, d, priority, current);
		index++;

	}
	printf("\n");
	fclose(file);

}

void add_todo(char *text, int priority) {
	FILE *file = fopen(FILE_NAME, "a+");
	if(file == NULL) {
		fprintf(stderr, "Could not open the todo file.\nDebug information: File: %s; Line: %i\n", __FILE__, __LINE__);
		exit(-1);
	}

	fprintf(file, "0|%i|%s\n", priority, text);
	fclose(file);
}

void remove_todo(int index) {
}

