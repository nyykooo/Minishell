# <sys/stat.h> e <sys/types.h>


## 1. _stat_

_int stat(const char *pathname, struct stat *statbuf);_

Usada para obter informações sobre um arquivo especificado por seu caminho.

-- const char *pathname: O caminho para o arquivo do qual você deseja obter informações.
-- struct stat *statbuf: Um ponteiro para uma estrutura stat onde as informações do arquivo serão armazenadas.

Obs: "A estrutura stat contém várias informações sobre o arquivo, como tamanho, permissões, data de modificação, etc. Aqui está uma versão simplificada da estrutura stat:
```
	struct stat {
		dev_t	st_dev;		// ID do dispositivo do arquivo
		ino_t	st_ino;		// Número do inode
		mode_t	st_mode;	// Modo de arquivo (permissões)
		nlink_t	st_nlink;	// Número de links
		uid_t	st_uid;		// ID do usuário proprietário
		gid_t	st_gid;		// ID do grupo proprietário
		off_t	st_size;	// Tamanho do arquivo em bytes
		time_t	st_atime;	// Data do último acesso
		time_t	st_mtime;	// Data da última modificação
		time_t	st_ctime;	// Data da última mudança nos metadados
	};
```

Retorno: 0 se as informações do arquivo forem obtidas com sucesso, ou -1 em caso de erro.


## 2. _lstat_

_int lstat(const char *pathname, struct stat *statbuf);_

Usada especificamente para obter informações sobre um link simbólico (ou symlink), em vez de seguir o link e obter informações sobre o arquivo para o qual o link aponta.

-- const char *pathname: O caminho para o link simbólico do qual você deseja obter informações.
-- struct stat *statbuf: Um ponteiro para uma estrutura stat onde as informações do link simbólico serão armazenadas.

Retorno: 0 se as informações do link simbólico forem obtidas com sucesso, ou -1 em caso de erro.

Obs: a estrutura lstat retornada é a mesma da stat.


## 3. _fstat_

_int fstat(int fd, struct stat *statbuf);_

Usada para obter informações sobre um arquivo associado a um descritor de arquivo específico. É semelhante à função stat(), mas em vez de usar o nome do arquivo, ela usa um descritor de arquivo previamente aberto.

-- int fd: O descritor de arquivo para o qual você deseja obter informações.
-- statbuf: Um ponteiro para uma estrutura stat onde as informações do arquivo serão armazenadas.

Retorno: 0 se as informações do arquivo forem obtidas com sucesso, ou -1 em caso de erro.

Obs: A estrutura stat retornada por fstat() tb é a mesma.