/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunhenr <brunhenr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 15:59:53 by brunhenr          #+#    #+#             */
/*   Updated: 2024/07/06 15:44:30 by brunhenr         ###   ########.fr       */
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
		if (current_cmd->input_file == true)
		{
			if (in_fd >= 0)
				close(in_fd);
			in_fd = open(current_cmd->cmd, O_RDONLY);
			if (in_fd < 0)
			{
				perror("open");
				exit(1);
			}
		}
		current_cmd = current_cmd->next;
	}
	return (in_fd);
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
		if (current_cmd->rappend == true || current_cmd->rtrunc == true)
		{
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
}

static bool	is_pipe_or_redir(t_cmd *cmd, int i)
{
	if (i == 0 && cmd->type == T_RTRUNC)
		return (false);
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

void	ft_exec(t_cmd *cmd_temp)
{
	char	**arg_array;
	char	*path;

	arg_array = ft_to_array(cmd_temp);
	path = get_command_path(cmd_temp->cmd);
	execve(path, arg_array, envvar_array(cmd_temp->shell));
	exit(0);
}

bool ft_has_pipe(t_cmd *cmd_temp)
{
	int		has_pipe;
	t_cmd	*temp;

	has_pipe = 0;
	temp = cmd_temp;
	while (temp != NULL)
	{
		if (temp->type == T_PIPE)
		{
			has_pipe = 1;
			break;
		}
		temp = temp->next;
	}
	return (has_pipe);
}

void	ft_nopipe(int in_fd, int out_fd, int fd1, int fd0)
{
	if (in_fd >= 0)
	{
		dup2(in_fd, STDIN_FILENO);
		close(in_fd);
		if (out_fd >= 0)
		{
			dup2(out_fd, STDOUT_FILENO);
			close(out_fd);
		}
		return ;
	}
	if (in_fd == -1)
	{	
		if (out_fd >= 0)
		{
			dup2(out_fd, STDOUT_FILENO);
			close(out_fd);
		}
		return ;
	}
	if (out_fd == -1)
	{
		dup2(fd1, STDOUT_FILENO);
		close(fd1);
		dup2(fd1, STDIN_FILENO);
		close(fd0);
		return ;
	}
	if (out_fd >= 0)
	{
		dup2(out_fd, STDOUT_FILENO);
		close(out_fd);
		close(in_fd);
		close(fd1);
		close(fd0);
		return ;
	}
}

void ft_haspipe(int in_fd, int fd1, int fd0)
{
	if (in_fd >= 0)
	{
		close(fd0);
		dup2(in_fd, STDIN_FILENO);
		close(in_fd);
		dup2(fd1, STDOUT_FILENO);
		close(fd1);
		return ;
	}	
	if (in_fd == -1)
	{
		close(fd0);
		dup2(fd1, STDOUT_FILENO);
		close(fd1);
		return ;
	}
}

void	create_pipe(int fd[2])
{
	if (pipe(fd) == -1)
	{
		perror("pipe");
		exit(1);
	}
}

pid_t create_child_process()
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		exit(2);
	}
	return (pid);
}

void manage_child(t_cmd *cmd_temp, int old_read_fd, int fd[2])
{
	int in_fd;
	int out_fd;

	in_fd = handle_input_redirection(cmd_temp);
	out_fd = handle_output_redirection(cmd_temp);
	if (old_read_fd != 0) // setting necessário quando há múltiplos pipes
	{
		dup2(old_read_fd, STDIN_FILENO);
		close(old_read_fd);
	}
	int has_pipe = ft_has_pipe(cmd_temp);
	if (has_pipe)
	{
		ft_haspipe(in_fd, fd[1], fd[0]);
		ft_exec(cmd_temp);
	}
	else
	{
		ft_nopipe(in_fd, out_fd, fd[1], fd[0]);
		ft_exec(cmd_temp);
	}
}

void manage_parent(int pid, int *old_read_fd, int fd[2])
{
	waitpid(pid, NULL, 0);
	if (*old_read_fd != 0)
		close(*old_read_fd);
	*old_read_fd = fd[0];
	close(fd[1]);
}
bool check_and_advance_cmd(t_cmd **cmd_temp, int *i)
{
	if ((is_pipe_or_redir(*cmd_temp, (*i)++) == true) || (is_file(*cmd_temp) == true))
	{
		*cmd_temp = (*cmd_temp)->next;
		return (true);
	}
	return (false);
}

int	handle_pipe_and_redir(t_cmd *commands)
{
	int		fd[2];
	int		old_read_fd;
	int		i;
	pid_t	pid;
	t_cmd	*cmd_temp;

	i = 0;
	cmd_temp = commands;
	old_read_fd = 0;
	while (cmd_temp != NULL)
	{	
		if (check_and_advance_cmd(&cmd_temp, &i))
			continue;
		create_pipe(fd);
		pid = create_child_process();
		if (pid == 0)
			manage_child(cmd_temp, old_read_fd, fd);
		else
			manage_parent(pid, &old_read_fd, fd);
		cmd_temp = cmd_temp->next;
	}
	if (old_read_fd != 0)
		close(old_read_fd);
	return (0);
}
