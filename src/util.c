#include "util.h"

#include <stdio.h>

void print_help(char *name) {
	char *line = "----------------------------------";
	printf("Todo:\n%s\ntodo is a cli tool to manage your todo list.\n\nUsage:\n%s\n\tShows the todo list if available\n%s add <thing> [priority]\n\tAdds an entry to the list\n%s remove [line]\n\tRemoves an entry\n%s clear\n\tClears the todo list\n", line, name, name, name, name);
}

