/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunhenr <brunhenr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 15:59:53 by brunhenr          #+#    #+#             */
/*   Updated: 2024/07/03 11:11:27 by brunhenr         ###   ########.fr       */
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

void	handle_input_redirection(t_cmd *cmd_temp)
{
	t_cmd	*current_cmd;
	int		in_fd;

	in_fd = -1;
	current_cmd = cmd_temp;
	while (current_cmd != NULL)
	{
		//printf("entrou no loop da input\n");
		//printf("current_cmd->input_file = %d\n", current_cmd->input_file);
		if (current_cmd->input_file == true)
		{
			//printf("entrou no if da input\n");
			if (in_fd >= 0)
				close(in_fd);
			in_fd = open(current_cmd->cmd, O_RDONLY);
			//printf("in_fd = %d\n", in_fd);
			if (in_fd < 0)
			{
				perror("open");
				exit(1);
			}
		}
		current_cmd = current_cmd->next;
	}
	if (in_fd >= 0)
	{
		dup2(in_fd, STDIN_FILENO);
		close(in_fd);
	}
}
/*error_msg = error_msg_construct(4, "-minishell: ", last_cmd->path, ": ", strerror(errno));
put_error_msg(error_msg, STDERR_FILENO); // Ajustar o EXIT_STATUS aqui
free(error_msg);
exit(EXIT_FAILURE);*/

void	handle_output_redirection(t_cmd *cmd_temp)
{
	t_cmd	*current_cmd;
	int		fd_out = -1;
	int		flags;

	current_cmd = cmd_temp;
	while (current_cmd != NULL)
	{
		printf("entrou no loop da output\n");
		if (current_cmd->rappend == true || current_cmd->rtrunc == true)
		{
			printf("entrou no if da output\n");
			flags = O_WRONLY | O_CREAT;
			if (current_cmd->rappend == true)
				flags |= O_APPEND;
			else
				flags |= O_TRUNC;
			if (fd_out >= 0)
				close(fd_out);
			fd_out = open(current_cmd->cmd, flags, 0644);
			if (fd_out < 0)
			{
				perror("open");
				exit(1);
			}
		}
		current_cmd = current_cmd->next;
	}
	if (fd_out >= 0)
	{
		dup2(fd_out, STDOUT_FILENO);
		close(fd_out);
	}
}

int	handle_pipe(t_cmd *commands)
{
	int		fd[2];
	int		old_read_fd;
	pid_t	pid;
	t_cmd	*cmd_temp;
	char	**arg_array;
	char	*path;

	cmd_temp = commands;
	old_read_fd = 0;
	while (cmd_temp != NULL && cmd_temp->type == T_COMMAND)
	{
		//printf("entrou no loop principal\n");
		if (pipe(fd) == -1)
		{
			perror("pipe");
			exit(1);
		}
		//printf("pipe criado\n");
		pid = fork();
		//printf("fork criado\n");
		if (pid < 0)
		{
			perror("fork");
			exit(2);
		}
		else if (pid == 0)
		{
			// Processo filho
			handle_input_redirection(cmd_temp);
			handle_output_redirection(cmd_temp);
			// Configurar pipe
			if (old_read_fd != 0)
			{
				dup2(old_read_fd, STDIN_FILENO);
				close(old_read_fd);
			}
			if (cmd_temp->next != NULL && cmd_temp->next->type == T_PIPE)
			{
				close(fd[0]); // Não precisa do lado de leitura do pipe no filho
				dup2(fd[1], STDOUT_FILENO);
				close(fd[1]);
			}
			arg_array = ft_to_array(cmd_temp);
			path = get_command_path(cmd_temp->cmd);
			execve(path, arg_array, envvar_array(cmd_temp->shell));
			exit(0); // Encerra o filho se execve falhar
		}
		else
		{
			// Processo pai
			waitpid(pid, NULL, 0); // Espera o filho terminar
			if (old_read_fd != 0)
				close(old_read_fd);
			old_read_fd = fd[0];
			close(fd[1]); // Fecha o lado de escrita do pipe no pai
		}
		if (cmd_temp->next != NULL && cmd_temp->next->type == T_PIPE)
			cmd_temp = cmd_temp->next->next; // Pula o token de pipe
		else
			break; // Sai do loop se não houver mais pipes
	}
	if (old_read_fd != 0)
		close(old_read_fd);
	return (0);
}
