# <unistd.h>

## 1. _access_

_int access(const char *pathname, int mode);_

Usada para verificar se um determinado arquivo pode ser acessado ou não com as permissões especificadas. Esta função é útil quando você precisa verificar se um arquivo existe ou se possui permissões específicas antes de realizar operações de leitura ou escrita nele.

-- const char *pathname: É o caminho para o arquivo que você deseja verificar.
-- int mode: São as permissões que você deseja verificar. Pode ser uma combinação de constantes, como R_OK para verificar a permissão de leitura, W_OK para verificar a permissão de escrita, X_OK para verificar a permissão de execução e F_OK para verificar a existência do arquivo.

Retorno: 0 se o acesso ao arquivo for permitido de acordo com as permissões especificadas, e -1 se ocorrer algum erro.

## 2. _fork_

_pid_t fork(void);_

Usada para criar um novo processo. Ambos os processos continuam a executar o mesmo programa a partir do ponto em que fork() foi chamado, mas cada um deles tem seu próprio espaço de endereço de memória e identificador de processo (PID).

(Sem argumentos)

-- Retorno: int

	* No processo pai, o valor retornado é o PID (identificador de processo) do processo filho.
	* No processo filho, o valor retornado é 0.
	* Se ocorrer um erro, o valor retornado é -1.

## 3. _getcwd_

_char *getcwd(char *buf, size_t size);_

Usada para obter o diretório de trabalho atual do processo.

-- char *buf: É um ponteiro para um buffer de caracteres onde o caminho do diretório será armazenado. Se buf for NULL, a função alocará dinamicamente um buffer suficientemente grande para armazenar o caminho.
-- size_t size: É o tamanho do buffer apontado por buf.

Retorno: string contendo o caminho absoluto do diretório de trabalho atual, ou NULL em caso de erro.

## 4. _chdir_

_int chdir(const char *path);_

Usada para alterar o diretório de trabalho atual do processo para o diretório especificado. Isso permite que você mude para um diretório diferente durante a execução do programa.

-- const char *path: É o caminho para o diretório para o qual você deseja mudar o diretório de trabalho atual.

Retorno: 0 se a operação for bem-sucedida e -1 em caso de erro.

## 5. _unlink_

_int unlink(const char *pathname);_

Usada para remover (ou "excluir") um arquivo do sistema de arquivos. Ela exclui o arquivo especificado pelo caminho fornecido.

-- const char *pathname: O caminho para o arquivo que você deseja excluir.

Retorno: 0 se a operação for bem-sucedida e -1 em caso de erro.

## 6. _execve_

_int execve(const char *pathname, char *const argv[], char *const envp[]);_

Usada para executar um programa a partir de um arquivo binário. Ele substitui o programa atual do processo pelo programa especificado e executa-o.

-- const char *pathname: O caminho para o arquivo binário do programa que você deseja executar.  
-- char *const argv: Um vetor de strings que representam os argumentos passados para o programa.  
-- char **const envp: Um vetor de strings que representam as variáveis de ambiente do programa. O último elemento deve ser NULL.  


Retorno: -1 em caso de erro e não retorna se for bem-sucedida.

## 7. _dup_

_int dup(int oldfd);_

Usada para duplicar um descritor de arquivo existente. Ela cria uma nova entrada na tabela de fds do processo, que se refere ao mesmo arquivo ou pipe que o fd original.

-- int oldfd: O descritor de arquivo que você deseja duplicar.

Retorno: novo fd se for bem-sucedida, ou -1 em caso de erro.

## 8. _dup2_

_int dup2(int oldfd, int newfd);_

Usada tambem para duplicar um fd existente. Porem, permite que você especifique explicitamente o número do novo fd. Ela duplica um fd existente para um número de fd específico.

-- int oldfd: O descritor de arquivo que você deseja duplicar.
-- int newfd: O número do novo descritor de arquivo.

Retorno: novo fd (ou newfd) se for bem-sucedida, ou -1 em caso de erro.

## 9. _pipe_

int pipe(int pipefd[2]);

Usada para criar um pipe, que é uma forma de comunicação interprocessual (IPC) que permite a comunicação entre dois processos

Obs: "Um pipe é uma sequência de bytes unidirecional e sem nome, que pode ser usada para enviar dados de um processo para outro."

-- int pipefd: Um array de inteiros de tamanho 2, onde o descritor de arquivo para a extremidade de leitura do pipe será armazenado em pipefd[0] e o descritor de arquivo para a extremidade de escrita do pipe será armazenado em pipefd[1].

Retorno: 0 se a operação for bem-sucedida, ou -1 em caso de erro.

## 10. _isatty_

_int isatty(int fd);_

Usada para verificar se um descritor de arquivo se refere a um terminal. Isso é útil para determinar se a entrada ou saída está sendo redirecionada para um arquivo ou se está interagindo diretamente com um terminal.

-- int fd: O descritor de arquivo que você deseja verificar.

Retorno: 1 se o descritor de arquivo estiver associado a um terminal (ou seja, se for um terminal), ou 0 se não estiver associado a um terminal.

## 11. _ttyname_

_char *ttyname(int fd);_

Usada para obter o nome do terminal associado a um determinado descritor de arquivo.

-- int fd: O descritor de arquivo para o qual você deseja obter o nome do terminal.

Retorno: string contendo o caminho do terminal associado ao descritor de arquivo especificado. Se o descritor de arquivo não estiver associado a um terminal, a função retorna NULL.

## 12. _ttyslot_

_int ttyslot(void);_

Usada para determinar o número da entrada de terminal do usuário no arquivo /etc/ttys. Essa função é principalmente usada em sistemas Unix para obter informações sobre a posição do terminal do usuário em relação aos outros terminais.

(Sem argumentos)

Retorno: número da entrada de terminal do usuário no arquivo /etc/ttys. Se ocorrer um erro, ou se o usuário não estiver conectado a um terminal, a função retorna -1.

## 13. _getenv_

_char *getenv(const char *name);_

Usada para obter o valor de uma variável de ambiente.

Obs: "As variáveis de ambiente são pares de chave-valor que são parte do ambiente de execução de um programa. Elas podem ser definidas no sistema operacional ou pelo próprio programa antes de sua execução."

-- const char *name: O nome da variável de ambiente que você deseja obter.

Retorno: string contendo o valor da variável de ambiente especificada. Se a variável de ambiente não estiver definida, a função retorna NULL.