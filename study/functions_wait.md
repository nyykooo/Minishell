# wait.h functions <sys/wait.h>  

##  _wait e wait3_

_pid_t wait(int *status);_

A função wait é usada para fazer o processo pai esperar até que um de seus processos filhos termine. A função também retorna o PID do processo filho que terminou e o status de saída do processo filho.

_pid_t wait3(int *status, int options, struct rusage *rusage);_

A função wait3 é semelhante à função wait, mas também retorna informações sobre os recursos usados pelo processo filho. A estrutura rusage é definida em <sys/resource.h>.

## _waitpid e wait4_

_pid_t waitpid(pid_t pid, int *status, int options);_

A função waitpid é semelhante à função wait, mas permite especificar o PID do processo filho que o processo pai deve esperar. Além disso, permite especificar opções adicionais.  

_pid_t wait4(pid_t pid, int *status, int options, struct rusage *rusage);_  

A função wait4 é semelhante à função waitpid, mas também retorna informações sobre os recursos usados pelo processo filho. A estrutura rusage é definida em <sys/resource>.h>.

# MACROS

## WIFEXITED(status)  
 Esta macro retorna um valor diferente de zero se o filho terminou normalmente, ou seja, através de uma chamada a exit ou retornando da função main. Se essa macro retornar verdadeiro, você pode usar a macro WEXITSTATUS(status) para obter o código de saída do processo filho.

## WIFSIGNALED(status)  
 Esta macro retorna um valor diferente de zero se o filho terminou devido ao recebimento de um sinal que não foi capturado. Se esta macro retornar verdadeiro, você pode usar a macro WTERMSIG(status) para obter o número do sinal que causou a terminação do processo filho.

## UNTRACED
A UNTRACED 

```
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    pid_t pid = fork();

    if (pid == -1) {
        // Erro ao criar o processo filho
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        // Este é o processo filho
        printf("Processo filho\n");
        exit(42);  // Termina com código de saída 42
    } else {
        // Este é o processo pai
        int status;
        waitpid(pid, &status, 0);  // Aguarda a terminação do filho

        if (WIFEXITED(status)) {
            printf("Filho terminou normalmente com código de saída %d\n", WEXITSTATUS(status));
        } else if (WIFSIGNALED(status)) {
            printf("Filho terminou devido ao sinal %d\n", WTERMSIG(status));
        } else {
            printf("Filho terminou de outra forma\n");
        }
    }

    return 0;
}
```