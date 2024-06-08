# <termios.h>

Essa biblioteca fornece funcionalidades para controla terminais. Como entrada e saida de dados, controle de fluxo, velocidade de transmissao e modos de operacao.

## 1. tcgetattr

### _**int tcgetattr** (int fd, struct termios *termios_p);_  
Obtém os parâmetros do terminal.

-- fd: Este é o descritor de arquivo do terminal. Normalmente, você usaria STDIN_FILENO  para o terminal padrão.  
-- termios_p: Este é um ponteiro para uma estrutura termios que será preenchida com os  atributos atuais do terminal.  

A função retorna 0 em caso de sucesso. Se ocorrer um erro, -1 é retornado e errno é  definido apropriadamente.

## 2. tcseetattr

### _**int tcsetattr** (int fd, int optional_actions, const struct termios *termios_p);_  
Define os parâmetros do terminal.  

-- fd: Este é o descritor de arquivo do terminal. Normalmente, você usaria STDIN_FILENO   para o terminal padrão.  
-- optional_actions: Este argumento determina quando os atributos do terminal são  alterados. Pode ser TCSANOW para alterar imediatamente, TCSADRAIN para alterar após todo o   output pendente ter sido transmitido, ou TCSAFLUSH para alterar após todo o output   pendente ter sido transmitido e descartar todo o input que ainda não foi lido.  
-- termios_p: Este é um ponteiro para uma estrutura termios que contém os novos atributos   do terminal.  

A função retorna 0 em caso de sucesso. Se ocorrer um erro, -1 é retornado e errno é  definido apropriadamente.  
