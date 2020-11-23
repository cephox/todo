#include "todo.h"

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

void print_help(char *name) {
	printf("Todo:\n-----------------------------------\nTodo is a cli to manage your todo list\n\nSyntax:\n%s add \"Thing to do\" [Priority (default: 1)]\n%s remove [line (starting at 1) (default: 1)]\n%s done [line (starting at 1) (default: 1)]\n\nAuthor: ce_phox\n", name, name, name);
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
		if(argc == 3)
			remove_todo(atoi(argv[2]));
		else
			remove_todo(1);
	} else if(strcmp(argv[1], "done") == 0) {
		if(argc == 3)
			done(atoi(argv[2]));
		else
			done(1);
	}

	return 0;
}

void print_todo() {

	printf("Index | Done | Priority | Thing to do\n");

	FILE *file = fopen(FILE_NAME, "r");
	if (file == NULL) {
		fprintf(stderr, "Could not open the todo file.\nDebug information: File: %s; Line: %i\n", __FILE__, __LINE__);
		exit(-1);
	}

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

void done(int index) {
	FILE *file = fopen(FILE_NAME, "r");
	if(file == NULL) {
		fprintf(stderr, "Could not open the todo file.\nDebug information: File: %s; Line: %i\n", __FILE__, __LINE__);
		exit(-1);
	}

	FILE *temp_file = fopen(".todo.temp", "w");
	if (temp_file == NULL) {
		fprintf(stderr, "Could not open the temp file.\nDebug information: File: %s; Line: %i\n", __FILE__, __LINE__);
		exit(-1);
	}

	size_t len;
	char *line = NULL;

	char *temp = NULL;

	index--;
	int current = 0;
	while(getline(&line, &len, file) != -1) {
		if(current == index) {
			temp = strtok(line, "|");
			temp = strtok(NULL, "|");

			int priority = atoi(temp);
			temp = strtok(NULL, "|");

			fprintf(temp_file, "1|%i|%s", priority, temp);

			continue;
		}
		fprintf(temp_file, "%s", line);
	}
	fclose(file);
	fclose(temp_file);

	remove(FILE_NAME);
	rename(".todo.temp", FILE_NAME);
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
	FILE *file = fopen(FILE_NAME, "r");
	if(file == NULL) {
		fprintf(stderr, "Could not open the todo file.\nDebug information: File: %s; Line: %i\n", __FILE__, __LINE__);
		exit(-1);
	}

	FILE *temp_file = fopen(".todo.temp", "w");
	if (temp_file == NULL) {
		fprintf(stderr, "Could not open the temp file.\nDebug information: File: %s; Line: %i\n", __FILE__, __LINE__);
		exit(-1);
	}

	size_t len;
	char *line;

	index--;
	int current = 0;

	while(getline(&line, &len, file) != -1) {
		if(current != index) {
			fprintf(temp_file, "%s", line);
		}
		current++;
	}

	fclose(file);
	fclose(temp_file);

	remove(FILE_NAME);
	rename(".todo.temp", FILE_NAME);

}

