/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunhenr <brunhenr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 15:59:53 by brunhenr          #+#    #+#             */
/*   Updated: 2024/07/04 19:14:58 by brunhenr         ###   ########.fr       */
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

int	handle_input_redirection(t_cmd *cmd_temp)
{
	t_cmd	*current_cmd;
	int		in_fd;

	in_fd = -1;
	current_cmd = cmd_temp;
	while (current_cmd != NULL && current_cmd->type != T_PIPE)
	{
		//printf("entrou no loop da input\n");
		//printf("e o current_cmd->cmd = %s\n", current_cmd->cmd);
		//printf("seu input_file eh : %d\n", current_cmd->input_file);
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
	return (in_fd);
	/*if (in_fd >= 0)
	{
		dup2(in_fd, STDIN_FILENO);
		close(in_fd);
	}*/
}
/*error_msg = error_msg_construct(4, "-minishell: ", last_cmd->path, ": ", strerror(errno));
put_error_msg(error_msg, STDERR_FILENO); // Ajustar o EXIT_STATUS aqui
free(error_msg);
exit(EXIT_FAILURE);*/

int	handle_output_redirection(t_cmd *cmd_temp)
{
	t_cmd	*current_cmd;
	int		fd_out;
	int		flags;

	fd_out = -1;
	current_cmd = cmd_temp;
	while (current_cmd != NULL)
	{
		//printf("entrou no loop da output\n");
		if (current_cmd->rappend == true || current_cmd->rtrunc == true)
		{
			//printf("entrou no if da output\n");
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
	return (fd_out);
	/*if (fd_out >= 0)
	{
		dup2(fd_out, STDOUT_FILENO);
		close(fd_out);
	}*/
}

static bool	is_pipe_or_redir(t_cmd *cmd, int i)
{
	if (i == 0 && cmd->type == T_RTRUNC)
	{
		printf("entrou");
		return (false);
	}
	if (cmd->type == T_RAPEND || cmd->type == T_RTRUNC || \
	cmd->type == T_LTRUNC || cmd->type == T_LAPEND || \
	cmd->type == T_PIPE)
		return (true);
	return (false);
}

static bool is_file(t_cmd *cmd)
{
	if (cmd->prev != NULL && (cmd->prev->type == T_RAPEND || \
	cmd->prev->type == T_RTRUNC || \
	cmd->prev->type == T_LTRUNC || \
	cmd->prev->type == T_LAPEND)) 
		return (true);
	return (false);
}

int	handle_pipe_and_redir(t_cmd *commands)
{
	int		fd[2];
	int		old_read_fd;
	pid_t	pid;
	t_cmd	*cmd_temp;
	char	**arg_array;
	char	*path;
	int	out_fd = -1;
	int	in_fd = -1;
	int	i = 0;

	cmd_temp = commands;
	old_read_fd = 0;
	//printf("cmd_temp->cmd = %s\n", cmd_temp->cmd);
	while (cmd_temp != NULL)
	{	
		printf("cmd_temp->cmd = %s\n", cmd_temp->cmd);
		if ((is_pipe_or_redir(cmd_temp, i) == true) || (is_file(cmd_temp) == true))
		{
			cmd_temp = cmd_temp->next;
			continue;
		}
		i++;
		if (pipe(fd) == -1)
		{
			perror("pipe");
			exit(1);
		}
		pid = fork();
		if (pid < 0)
		{
			perror("fork");
			exit(2);
		}
		else if (pid == 0)
		{
			in_fd = handle_input_redirection(cmd_temp);
			out_fd = handle_output_redirection(cmd_temp);
			// setting necessario quando ha multiplos pipes
			if (old_read_fd != 0)
			{
				dup2(old_read_fd, STDIN_FILENO);
				close(old_read_fd);
			}
			int has_pipe = 0;
			t_cmd *temp = cmd_temp;
			while (temp != NULL)
			{
				if (temp->type == T_PIPE)
				{
					has_pipe = 1;
					break;
				}
				temp = temp->next;
			}
			if (has_pipe && in_fd >= 0) // Se houver redirecionamento de input
			{
				printf("PIPE [x] REDIR [x]\n");
				printf("cmd_temp->cmd = %s\n", cmd_temp->cmd);
				printf("in_fd = %d\n", in_fd);
				printf("out_fd = %d\n", out_fd);
				printf("fd[0] = %d\n", fd[0]);
				printf("fd[1] = %d\n", fd[1]);
				close(fd[0]); // Não precisa do lado de leitura do pipe no filho
				dup2(in_fd, STDIN_FILENO);
				close(in_fd);
				dup2(fd[1], STDOUT_FILENO);
				close(fd[1]);
				arg_array = ft_to_array(cmd_temp);
				path = get_command_path(cmd_temp->cmd);
				execve(path, arg_array, envvar_array(cmd_temp->shell));
				exit(0); // Encerra o filho se execve falhar
			}
			if (has_pipe && in_fd == -1)
			{
				close(fd[0]); // Não precisa do lado de leitura do pipe no filho
				dup2(fd[1], STDOUT_FILENO);
				close(fd[1]);
				arg_array = ft_to_array(cmd_temp);
				path = get_command_path(cmd_temp->cmd);
				execve(path, arg_array, envvar_array(cmd_temp->shell));
				exit(0); // Encerra o filho se execve falhar
			}
			if (!has_pipe && in_fd >= 0)
			{
				printf("PIPE [ ] IN_REDIR [x]\n");
				printf("cmd_temp->cmd = %s\n", cmd_temp->cmd);
				printf("in_fd = %d\n", in_fd);
				printf("out_fd = %d\n", out_fd);
				printf("fd[0] = %d\n", fd[0]);
				printf("fd[1] = %d\n", fd[1]);
				dup2(in_fd, STDIN_FILENO);
				close(in_fd);
				if (out_fd >= 0)
				{
					dup2(out_fd, STDOUT_FILENO);
					close(out_fd);
				}
				arg_array = ft_to_array(cmd_temp);
				path = get_command_path(cmd_temp->cmd);
				execve(path, arg_array, envvar_array(cmd_temp->shell));
				exit(0); // Encerra o filho se execve falhar
			}
			if (!has_pipe && in_fd == -1)
			{	
				printf("PIPE [ ] REDIR [ ]\n");
				printf("cmd_temp->cmd = %s\n", cmd_temp->cmd);
				printf("in_fd = %d\n", in_fd);
				printf("out_fd = %d\n", out_fd);
				printf("fd[0] = %d\n", fd[0]);
				printf("fd[1] = %d\n", fd[1]);
				if (out_fd >= 0)
				{
					dup2(out_fd, STDOUT_FILENO);
					close(out_fd);
				}
				arg_array = ft_to_array(cmd_temp);
				path = get_command_path(cmd_temp->cmd);
				execve(path, arg_array, envvar_array(cmd_temp->shell));
				exit(0); // Encerra o filho se execve falhar
			}
			if (!has_pipe && out_fd == -1)
			{
				printf("PIPE [ ] OUT_REDIR [ ]\n");
				printf("cmd_temp->cmd = %s\n", cmd_temp->cmd);
				printf("in_fd = %d\n", in_fd);
				printf("out_fd = %d\n", out_fd);
				printf("fd[0] = %d\n", fd[0]);
				printf("fd[1] = %d\n", fd[1]);
				dup2(fd[1], STDOUT_FILENO);
				close(fd[1]);
				dup2(fd[0], STDIN_FILENO);
				close(fd[0]);
				arg_array = ft_to_array(cmd_temp);
				path = get_command_path(cmd_temp->cmd);
				execve(path, arg_array, envvar_array(cmd_temp->shell));
				exit(0); // Encerra o filho se execve falhar
			}
			if (!has_pipe && out_fd >= 0)
			{
				printf("PIPE [ ] OUT_REDIR [X]\n");
				printf("cmd_temp->cmd = %s\n", cmd_temp->cmd);
				printf("tem pipe e in_fd >= 0\n");
				printf("in_fd = %d\n", in_fd);
				printf("out_fd = %d\n", out_fd);
				printf("fd[0] = %d\n", fd[0]);
				printf("fd[1] = %d\n", fd[1]);
				dup2(out_fd, STDOUT_FILENO);
				close(out_fd);
				close(in_fd);
				close(fd[1]);
				close(fd[0]);
				arg_array = ft_to_array(cmd_temp);
				path = get_command_path(cmd_temp->cmd);
				execve(path, arg_array, envvar_array(cmd_temp->shell));
				exit(0); // Encerra o filho se execve falhar
			}
		}
		else
		{
			// Processo pai
			waitpid(pid, NULL, 0); // Espera o filho terminar
			if (old_read_fd != 0)
				close(old_read_fd);
			old_read_fd = fd[0];
			close(fd[1]); // Fecha o lado de escrita do pipe no pai
			//pq nao posso fechar o fd[0] aqui?
		}
		if (cmd_temp->next != NULL)
			cmd_temp = cmd_temp->next;
		else
			break;
	}
	if (old_read_fd != 0)
		close(old_read_fd);
	return (0);
}
