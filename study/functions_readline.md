# <readline/readline.h>

Quando você compilar um programa que usa a GNU Readline Library, é necessário vincular a biblioteca ao seu programa. Isso geralmente é feito adicionando -lreadline ao comando de compilação.

## 1. _readline_

#include <readline/readline.h>  
#include <readline/history.h>

_char *readline(const char *prompt);_

Usada para ler uma linha de entrada do usuário.

-- _const char *prompt_:  Mensagem de prompt que será exibida ao usuário ao solicitar a entrada. Pode ser uma string estática ou dinâmica.

Retorno: string contendo a linha de entrada digitada pelo usuário.

The line returned has the final newline removed, so only the text remains.

```
#include <stdio.h>
#include <readline/readline.h> \\ Not part of C standard. Installation required. Its GNU project
#include <stdlib.h>

int main() {
    char* line = readline("Digite algo: ");
    printf("Você digitou: %s\n", line);
    free(line);
    return 0;
}
```

## 2.  _add_history_

#include <readline/history.h>

_void add_history(const char *line);_

Usada para adicionar uma linha ao histórico de comandos. Isso permite que os usuários recuperem facilmente comandos anteriores usando as teclas de seta para cima e para baixo, por exemplo, para navegar pelo histórico de comandos.

-- const char *line: É a string que você deseja adicionar ao histórico de comandos.

(Sem retorno)

## 3. _rl_clear_history_

#include <readline/history.h>

_void rl_clear_history(void);_

Usada para limpar o histórico de comandos. Esta função remove todos os itens do histórico, ou seja, todas as linhas de entrada que foram lidas e armazenadas no histórico durante a sessão atual de execução do programa.

(Sem argumentos e retorno)

```
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
```

## 4. _rl_on_new_line_

#include <readline/readline.h>

_int rl_on_new_line(void);_

Usada para informar à biblioteca que o cursor de entrada deve ser movido para a próxima linha quando o usuário pressionar Enter. Isso é útil quando você deseja fazer alguma manipulação antes de exibir o próximo prompt, como no caso de um prompt multi-linha. Retorna 0 em caso de sucesso.

(Sem argumentos)


## 5. _rl_replace_line_

#include <readline/readline.h>

_int rl_replace_line(const char *text, int clear_undo);_

Usada para substituir a linha de entrada atual na tela por uma nova linha especificada. Isso é útil quando você deseja modificar a linha de entrada antes de exibi-la novamente na tela. Ela retorna 0 e caso de sucesso.

-- const char *text: É a nova linha de texto que você deseja exibir na tela.
-- int clear_undo: Se for diferente de zero, limpa o histórico de desfazer (undo history) para esta linha.

```
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
```

## 6. _rl_redisplay_

#include <readline/history.h>

_void rl_redisplay(void);_

Usada para dar redisplay da linha de entrada atual na tela. Ela é útil quando você precisa forçar a atualização da linha de entrada, por exemplo, após uma modificação feita programaticamente.

(Sem argumentos e retorno)

```
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
```