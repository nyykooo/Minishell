/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunhenr <brunhenr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 15:59:53 by brunhenr          #+#    #+#             */
/*   Updated: 2024/06/26 17:55:17 by brunhenr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libs/headers.h"

static char	*get_command_path(char *command)
{
	char	*path;
	char	**dirs;
	char	*possible_path;
	int		i;

	if (access(command, X_OK) == 0)
			return (command);
	path = getenv ("PATH");
	dirs = ft_split (path, ':');
	i = -1;
	while (dirs[++i] != NULL)
	{
		possible_path = malloc (strlen(dirs[i]) + strlen(command) + 2);
		strcpy (possible_path, dirs[i]);
		strcat (possible_path, "/");
		strcat (possible_path, command);
		if (access(possible_path, X_OK) == 0)
		{
			free(dirs);
			return (possible_path);
		}
		free (possible_path);
	}
	i = 0;
	while (dirs[i] != NULL)
		free(dirs[i++]);
	free(dirs);
	return (NULL);
}

int handle_pipe(t_cmd *commands)
{
	int fd[2];
	int old_read_fd = 0;
	pid_t pid;
	t_cmd *temp = commands;

	while (temp != NULL && temp->type == T_COMMAND)
	{
		if (pipe(fd) == -1)
		{
			perror("pipe");
			exit(1);
		}
		pid = fork();
		if (pid < 0) {
			perror("fork");
			exit(2);
		}
		else if (pid == 0)
		{ // Processo filho
			if (old_read_fd != 0)
			{
				dup2(old_read_fd, STDIN_FILENO);
				close(old_read_fd);
			}
			if (temp->next != NULL && temp->next->type == T_PIPE)
			{
				close(fd[0]); // Não precisa do lado de leitura do pipe no filho
				dup2(fd[1], STDOUT_FILENO);
				close(fd[1]);
			}
			char **arg_array = ft_to_array(temp);
			char *path = get_command_path(temp->cmd);
			execve(path, arg_array, envvar_array(temp->shell));
			exit(0); // Encerra o filho se execve falhar
		} 
		else
		{ // Processo pai
			waitpid(pid, NULL, 0); // Espera o filho terminar
			if (old_read_fd != 0)
			{
				close(old_read_fd);
			}
			old_read_fd = fd[0];
			close(fd[1]); // Fecha o lado de escrita do pipe no pai
		}

		if (temp->next != NULL && temp->next->type == T_PIPE)
		{
			temp = temp->next->next; // Pula o token de pipe
		}
		else
		{
			break; // Sai do loop se não houver mais pipes
		}
	}
	if (old_read_fd != 0) //
	{
		close(old_read_fd);
	}
	return 0;
}
/*int	handle_pipe(t_cmd *commands)
{
	int	fd[2];
	int	pid1;
	int	pid2;
	char **arg_array1;
	char **arg_array2;
	t_cmd *temp;
	char *path1;
	char *path2;
	int old_read_fd;
	int	i = 0;

	old_read_fd = 0;
	temp = commands;
	while (temp != NULL)
	{
		printf("temp->cmd: %s\n", temp->cmd);
		printf("temp-->cmd->type: %d\n", temp->type);
		temp = temp->next;
	}
	temp = commands;
	arg_array1 = ft_to_array(commands);
	temp = temp->next->next;
	arg_array2 = ft_to_array(temp);
	path1 = get_command_path(commands->cmd);
	path2 = get_command_path(temp->cmd);
	printf("path1: %s\n", path1);
	printf("path2: %s\n", path2);
	while (arg_array1[i] != NULL)
	{
		printf("arg_array1: %s\n", arg_array1[i]);
		i++;
	}
	i = 0;
	while (arg_array2[i] != NULL)
	{
		printf("arg_array2: %s\n", arg_array2[i]);
		i++;
	}
	if (pipe(fd) == -1)
	{
		perror("pipe");
		exit (1);
	}
	pid1 = fork();
	if (pid1 < 0)
	{
		perror("fork");
		exit (2);
	}
	if (pid1 == 0)
	{
		// Estamos no processo para a execucao do comando a esquerda do pipe
		// Fechar o descritor de leitura.
		close(fd[0]);
		// Redirecionar a saida padrao para o descritor de escrita da pipe.
		dup2(fd[1], STDOUT_FILENO); // STDOUT_FILENO = 1
		close(fd[1]);
		execve(path1, arg_array1, envvar_array(commands->shell));
	}
	// Todo o codigo apos a execve() nao sera executado (pelo filho), pois o processo filho foi substituido pelo ping.
	pid2 = fork();
	if (pid2 == -1)
	{
		perror("fork");
		exit (3);
	}
	if (pid2 == 0)
	{
		// Estamos no processo filho para a execucao do comando a direita do pipe.	
		// Fechar o descritor de escrita criado pela pipe.
		close(fd[1]);
		// Redirecionar a entrada padrao para o descritor de leitura da pipe.
		dup2(fd[0], STDIN_FILENO); // STDIN_FILENO = 0
		close(fd[0]);
		execve(path2, arg_array2, envvar_array(commands->shell));
	}
	// Estamos no processo pai
	close(fd[1]);
	if (old_read_fd != 0)
		close(old_read_fd);
	old_read_fd = fd[0];
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	return (0);
}*/