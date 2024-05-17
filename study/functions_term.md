# <term.h>

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