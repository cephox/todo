#include "file.h"
#include "globals.h"

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <pwd.h>
#include <string.h>
#include <stdio.h>

char *get_dir() {
	struct passwd *pw = getpwuid(getuid());
	char *home = pw->pw_dir;
	strcat(home, "/.config/todo");
	return home;
}

char *get_file_name() {
	char *home = get_dir();
	strcat(home, "/");
	strcat(home, FILE_NAME);
	return home;
}

void create_file() {
	if(access(get_file_name(), F_OK) == 0)
		return;
	create_folder();
	FILE *fp = fopen(get_file_name(), "w+");
	fclose(fp);
}

void create_folder() {
	mkdir(get_dir(), 0755);
}

FILE *get_file(char *mode) {
	create_file();
	FILE *fp = fopen(get_file_name(), mode);
	return fp;
}

void append_data(char *data) {
	FILE *fp = get_file("a");
	fprintf(fp, "%s", data);
}

