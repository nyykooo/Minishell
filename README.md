# Minishell  
![GNU and Penguin](https://www.gnu.org/graphics/gnu-and-penguin-color-300x276.jpg)

Para suprimir a listagem dos detalhes dos leaks da _readline_ podemos usar:  
valgrind --leak-check=full --show-leak-kinds=all --suppressions=readline.supp

# The new allowed functions  
## <dirent.h>

### 15. _opendir_  

_DIR *opendir(const char *name);_  
Abre um diretório.

### 16. _readdir_

_struct dirent *readdir(DIR *dirp);_  
**Lê a próxima entrada de um diretório.**

### 17. _closedir_

_int closedir(DIR *dirp);_  
Fecha um diretório.

## <termios.h>

### 18. _tceetattr_

_int tcsetattr(int fd, int optional_actions, const struct termios *termios_p);_  
Define os parâmetros do terminal.  

### 19. _tcgetattr_

_int tcgetattr(int fd, struct termios *termios_p);_  
Obtém os parâmetros do terminal.  

## <term.h>

### 20. _tgettent_

_int tgetent(char *bp, const char *name);_  
**Carrega a entrada do terminal.**

### 21. _tgetflag_  

_int tgetflag(char *id);_  
Retorna o valor da capacidade do terminal.  

### 22. _tgetnum_  

_int tgetnum(char *id);_
Retorna o valor numérico da capacidade do terminal.  

### 23. _tgetstr_  

_char *tgetstr(char *id, char **area);_  
Retorna a string da capacidade do terminal.

### 24. _tgoto_  

_char *tgoto(const char *cap, int col, int row);_
Retorna uma string de cursor de movimento.  

### 25. _tputs_

_int tputs(const char *str, int affcnt, int (*putc)(int));_
Aplica preenchimento ao caractere e escreve no terminal.  

## <sys.ioctl.h>

### 26. _ioctl_

_int ioctl(int fd, unsigned long request, ...);_
Controla o dispositivo.  

## wait.h functions <sys/wait.h>  

### 34/35. _wait e wait3_

_pid_t wait(int *status);_

A função wait é usada para fazer o processo pai esperar até que um de seus processos filhos termine. A função também retorna o PID do processo filho que terminou e o status de saída do processo filho.

_pid_t wait3(int *status, int options, struct rusage *rusage);_

A função wait3 é semelhante à função wait, mas também retorna informações sobre os recursos usados pelo processo filho. A estrutura rusage é definida em <sys/resource>.h>.

### 36/37. _waitpid e wait4_

_pid_t waitpid(pid_t pid, int *status, int options);_

A função waitpid é semelhante à função wait, mas permite especificar o PID do processo filho que o processo pai deve esperar. Além disso, permite especificar opções adicionais.  

_pid_t wait4(pid_t pid, int *status, int options, struct rusage *rusage);_  

A função wait4 é semelhante à função waitpid, mas também retorna informações sobre os recursos usados pelo processo filho. A estrutura rusage é definida em <sys/resource>.h>.

### Work in progress...

#### Authors: Nicholas Campbell (ncampbel) e Bruno Henrique Lopes (brunhenr)
