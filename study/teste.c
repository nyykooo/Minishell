#include <stdio.h>
#include <readline/readline.h>
#include <stdlib.h>
#include <readline/history.h>
#include <unistd.h>

int main() {
    char	*line;
	char	*dir;
	
	dir = getcwd(NULL, 0);
	line = readline(dir);
    printf("Você digitou: %s\n", line);
	add_history(line);
	line = readline(dir);
    printf("Você digitou: %s\n", line);
	add_history(line);
	line = readline(dir);
    printf("Você digitou: %s\n", line);
    free(line);
	clear_history();
    return 0;
}