# _pipe()_
Um pipe é um mecanismo de IPC (Inter-Process Communication) que permite a comunicação unidirecional entre processos. Ele consiste em um buffer e dois descritores de arquivo: um para leitura (fd[0]) e outro para escrita (fd[1]).

## Sobre o buffer da _pipe()_
O buffer do pipe é uma parte fundamental do mecanismo de IPC do pipe (Inter-Process Communication).  
Ele é uma área de armazenamento temporário na memória usada para manter os dados que são transferidos de um processo para outro através do uso da _pipe()_. Quando um processo escreve dados no fd[1], esses dados são armazenados no buffer do pipe até que sejam lidos pelo processo receptor.

- **Tamanho do Buffer**: O tamanho do buffer de um pipe varia entre diferentes sistemas operacionais e configurações. Em muitos sistemas Linux, por exemplo, o tamanho padrão do buffer é de 65536 bytes (64 KiB), mas isso pode ser ajustado pelo sistema ou pelo administrador.
- **Comunicação Bloqueante e Não Bloqueante**: Por padrão, a leitura de um pipe é bloqueante, o que significa que o processo leitor será suspenso até que haja dados disponíveis para leitura. Da mesma forma, a escrita em um pipe cheio é bloqueante, o que significa que o processo escritor será suspenso até que haja espaço disponível no buffer. No entanto, é possível configurar um pipe para operações não bloqueantes, permitindo que o processo continue executando mesmo se a operação de leitura ou escrita não puder ser concluída imediatamente.
- **Comportamento FIFO**: O pipe opera em um princípio FIFO (First In, First Out), o que significa que os dados são lidos na mesma ordem em que foram escritos. Isso garante uma comunicação sequencial e ordenada entre processos.
- **Sincronização**: O buffer do pipe também serve como um ponto de sincronização entre processos. Por exemplo, se um processo tenta ler de um pipe vazio, ele será bloqueado até que outro processo escreva no pipe. Isso permite que os processos coordenem suas ações sem a necessidade de mecanismos de sincronização explícitos.
- **Limitações**: Embora os pipes sejam úteis para comunicação entre processos, a capacidade limitada do buffer e o comportamento bloqueante podem ser desvantagens em algumas situações. Para grandes volumes de dados ou comunicação mais complexa, outros mecanismos de IPC, como sockets ou memória compartilhada, podem ser mais apropriados.

```
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <errno.h>


//
// Este programa ira criar um pipe. E tambem criara 1 processo filho. 
// Cada processo ira fazer a soma de metade do array de ints.
//

int	main(int argc, char *argv[])
{
	int	arr[8] = { 1, 3, 5, 7, 2, 4, 6, 8 };
	int	fd[2];
	// A chamada da funcao pipe a seguir ira automaticamente armazenar os descritores de arquivo.
	// fd[0] - leitura e fd[1] - escrita
	int	id;
	int	start;
	int	end;
	int	sum;
	int	sum_from_child;
	int	i;

	if (pipe(fd) == -1) // a funcao pipe abre -faz o open()- automaticamente os descritores de arquivo
	{
		perror("pipe");
		exit (1);
	}

	printf("Pipe criado\n");
	printf("fd[0] = %d\n", fd[0]);
	printf("fd[1] = %d\n", fd[1]);

	id = fork();
	if (id == -1)
		exit (2);

	if (id == 0) // processo filho ira fazer a soma do 0 ao 5
	{
		start = 0;
		end = 4;
	}
	else // processo pai ira fazer a soma do 5 ao 10
	{
		start = 4;
		end = 8;
	}

	i = start;
	sum = 0;
	while (i < end)
	{
		sum += arr[i];
		i++;
	}
	printf("Soma parcial calculada = %d\n", sum); // As somas sao executadas em paralelo por ambos processos
	
	if (id == 0)
	{
		close (fd[0]);
		write(fd[1], &sum, sizeof(sum)); // O processo filho escreve a soma parcial no pipe
		close (fd[1]);
	}
	else
	{
		sum_from_child = 0;
		close (fd[1]);
		read(fd[0], &sum_from_child, sizeof(sum_from_child));
		close (fd[0]);

		int total_sum = sum + sum_from_child;
		printf("Soma total = %d\n", total_sum);
		wait(NULL); // Aguarda o processo filho terminar
	}
	exit (0);
}


```