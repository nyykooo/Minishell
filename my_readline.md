27. readline
char *readline(const char *prompt);

It reads the prompt input line.

#include <stdio.h>
#include <readline/readline.h> \\ Not part of C standard. Installation required. Its GNU project
#include <stdlib.h>

int main() {
    char* line = readline("Digite algo: ");
    printf("Você digitou: %s\n", line);
    free(line);
    return 0;
}
28. add_history
void add_history(const char *line);

It's used to add a line to the commands history. The line goes to the last position. There are a limited number of lines. This function do not copy the string passed as argument, so you don't have to free the string while using the history.

29. rl_clear_history
void rl_clear_history(void);

Simply clean the command history. There aren't arguments, nether a return.

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h> \\ Note this header

int main() {
    char* line = readline("Digite algo: ");
    add_history(line);

    // Limpa o histórico
    rl_clear_history();

    free(line);
    return 0;
}
30. rl_on_new_line
int rl_on_new_line(void);

It's used to inform the readline lib that the cursor was moved to a new line. In this way, the library keeps placing the cursor correctly. Ther aren't arguments, but it returns 0 in case of success.

31. rl_replace_line
int rl_replace_line(const char *text, int clear_undo);

It's used to replace the content of the line thats is being edited. The readline lib has an undo buffer. Its a intern struc that keeps the operations did. Like inserting/deleting caracters, movinf cursor, etc. clear_undo = 0, undo buffer keeps its content. Clear_undo = any number, undo buffer is cleaned. The function returns zero in case of success.

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

int main() {
    char* line = readline("Digite algo: ");
    add_history(line);

    // Substitui a linha atual
    rl_replace_line("Nova linha", 0);

    free(line);
    return 0;
}
32. rl_redisplay
void rl_redisplay(void);

It's used to "redraw" the actual line.

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

int main() {
    char* line = readline("Digite algo: ");
    add_history(line);

    // Substitui a linha atual
    rl_replace_line("Nova linha", 0);

    // Redesenha a linha atual
    rl_redisplay();

    free(line);
    return 0;
}