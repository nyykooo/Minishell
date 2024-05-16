# Minishell  
![GNU and Penguin](https://www.gnu.org/graphics/gnu-and-penguin-color-300x276.jpg)

Para suprimir a listagem dos detalhes dos leaks da _readline_ podemos usar:  
valgrind --leak-check=full --show-leak-kinds=all --suppressions=readline.supp

# The new allowed functions  
## <unistd.h>

### 1. _getcwd_

_char *getcwd(char *buf, size_t size);_  
Obtém o caminho do diretório de trabalho atual.

### 2. _chdir_

_int chdir(const char *path);_  
Muda o diretório de trabalho atual.

### 3. _unlink_

_int unlink(const char *pathname);_  
Remove o link para um arquivo.

### 4. _execve_

_int execve(const char *filename, char *const argv[], char *const envp[]);_  
Executa um programa.

### 5/6. _dup e dup2_

_int dup(int oldfd);_  
_int dup2(int oldfd, int newfd);_  
Duplica um descritor de arquivo. A dup2 duplica para um fd especifico.

### 7. _pipe_

_int pipe(int pipefd[2]);_  
Cria um pipe.

### 8. _isatty_

_int isatty(int fd);_  
Verifica se o descritor de arquivo se refere a um terminal.

### 9. _ttyname_

_char *ttyname(int fd);_  
Retorna o nome do terminal.

### 10. _ttyslot_

_int ttyslot(void);_  
Retorna o índice do terminal no arquivo utmp.  

### 11. _getenv_

_char *getenv(const char *name);_  
Obtém o valor de uma variável de ambiente.

## <sys.stat.h>

### 12. _stat_

_int stat(const char *restrict path, struct stat *restrict buf);_  
Obtém informações sobre um arquivo.

### 13. _lstat_

_int lstat(const char *restrict path, struct stat *restrict buf);_  
Semelhante ao stat, mas se o arquivo for um link simbólico, retorna informações sobre o link em si, não o arquivo que ele aponta.

### 14. _fstat_

_int fstat(int fd, struct stat *buf);_
Obtém informações sobre um arquivo, com base em um descritor de arquivo aberto.

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

### 33. _fork_

_pid_t fork(void);_  

A função fork é usada para criar um novo processo. O novo processo é uma cópia exata do processo que chamou fork, exceto por alguns valores que são alterados, como o PID (Process ID).

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
