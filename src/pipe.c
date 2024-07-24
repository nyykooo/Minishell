/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunhenr <brunhenr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 15:59:53 by brunhenr          #+#    #+#             */
/*   Updated: 2024/07/24 11:33:33 by brunhenr         ###   ########.fr       */
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
		possible_path = malloc (ft_strlen(dirs[i]) + ft_strlen(command) + 2);
		ft_strcpy (possible_path, dirs[i]);
		ft_strcat (possible_path, "/");
		ft_strcat (possible_path, command);
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
		if (current_cmd->type == T_LAPEND)
		{
			if (in_fd >= 0)
				close(in_fd);
			if (current_cmd->prev)
				in_fd = current_cmd->prev->here_doc_fd;
		}
		current_cmd = current_cmd->next;
	}
	return (in_fd);
}
/*error_msg = error_msg_construct(4, "-minishell: ", last_cmd->path, ": ", strerror(errno));
put_error_msg(error_msg, STDERR_FILENO); // Ajustar o EXIT_STATUS aqui
free(error_msg);
exit(EXIT_FAILURE);*/

int determine_flags(t_cmd *cmd_temp)
{
	int	flags;

	flags = O_WRONLY | O_CREAT;
	if (cmd_temp->rappend == true)
		flags |= O_APPEND;
	else
		flags |= O_TRUNC;
	return (flags);
}

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
			flags = determine_flags(current_cmd);
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

static bool	is_file(t_cmd *cmd)
{
	if (cmd->prev != NULL && (cmd->prev->type == T_RAPEND || \
	cmd->prev->type == T_RTRUNC || \
	cmd->prev->type == T_LTRUNC || \
	cmd->prev->type == T_LAPEND))
		return (true);
	return (false);
}
bool	is_builtin(char *cmd)
{
	if (ft_strcmp(cmd, "echo") == 0 || ft_strcmp(cmd, "cd") == 0 || \
	ft_strcmp(cmd, "pwd") == 0 || ft_strcmp(cmd, "export") == 0 || \
	ft_strcmp(cmd, "unset") == 0 || ft_strcmp(cmd, "env") == 0 || \
	ft_strcmp(cmd, "exit") == 0)
		return (true);
	return (false);
}
void	ft_exec_builtin(t_minishell *shell, t_cmd *cmd_temp)
{
		if (ft_strcmp(cmd_temp->cmd, "cd") == 0)
			handle_cd(cmd_temp, shell);
		else if (ft_strcmp(cmd_temp->cmd, "echo") == 0)
			handle_echo(cmd_temp);
		else if (ft_strcmp(cmd_temp->cmd, "exit") == 0)
			handle_exit(cmd_temp, shell);
		else if (ft_strcmp(cmd_temp->cmd, "export") == 0)
			handle_export(shell);
		else if (ft_strcmp(cmd_temp->cmd, "unset") == 0)
			handle_unset(cmd_temp, &shell->envvars);
		else if (ft_strcmp(cmd_temp->cmd, "env") == 0)
			handle_env(shell->envvars, shell, cmd_temp);
		else if (ft_strcmp(cmd_temp->cmd, "pwd") == 0)
			handle_pwd(shell);
}

void	ft_exec(t_minishell *shell, t_cmd *cmd_temp)
{
	char	**arg_array;
	char	*path;

	if (is_builtin(cmd_temp->cmd) == true)
	{
		ft_exec_builtin(shell, cmd_temp); //implementar o envio para o pai do exit_status e de erro
		exit(0);
	}
	arg_array = ft_to_array(cmd_temp);
	path = get_command_path(cmd_temp->cmd);
	if (execve(path, arg_array, envvar_array(cmd_temp->shell)) == -1)
	{
    	perror("execve");
    	exit(EXIT_FAILURE);
	}
}

bool	ft_has_pipe(t_cmd *cmd_temp)
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
			break ;
		}
		temp = temp->next;
	}
	return (has_pipe);
}

void	ft_nopipe(int in_fd, int out_fd)
{
	if (in_fd >= 0)
	{
		dup2(in_fd, STDIN_FILENO);
		close(in_fd);
	}
	if (out_fd >= 0)
	{
		dup2(out_fd, STDOUT_FILENO);
		close(out_fd);
	}
}

void	ft_haspipe(int in_fd, int fd1, int fd0)
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

pid_t	create_child_process(void)
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

void	ft_close_filefds(int in_fd, int out_fd)
{
	if (in_fd >= 0)
		close(in_fd);
	if (out_fd >= 0)
		close(out_fd);
}

void	manage_child(t_minishell *shell, t_cmd *cmd_temp, int old_read_fd, int fd[2])
{
	int	in_fd;
	int	out_fd;
	int	has_pipe;

	in_fd = handle_input_redirection(cmd_temp);
	out_fd = handle_output_redirection(cmd_temp);
	//printf("in_fd: %d\n", in_fd);
	//printf("out_fd: %d\n", out_fd);
	//printf("old_read_fd: %d\n", old_read_fd);
	if (old_read_fd != 0)
	{
		dup2(old_read_fd, STDIN_FILENO);
		close(old_read_fd);
	}
	has_pipe = ft_has_pipe(cmd_temp);
	//printf("has_pipe: %d\n", has_pipe);
	if (has_pipe)
	{
		ft_haspipe(in_fd, fd[1], fd[0]);
		ft_exec(shell, cmd_temp);
	}
	else
	{
		ft_nopipe(in_fd, out_fd);
		ft_exec(shell, cmd_temp);
	}
	ft_close_filefds(in_fd, out_fd);
}

void	manage_parent(int pid, int *old_read_fd, int fd[2], int *status)
{
	waitpid(pid, status, WNOHANG);
	//printf("pid: %d\n", pid);
	if (*old_read_fd != 0)
		close(*old_read_fd);
	*old_read_fd = fd[0];
	close(fd[1]);
}

bool	check_and_advance_cmd(t_cmd **cmd_temp, int *i)
{
	if ((is_pipe_or_redir(*cmd_temp, (*i)++) == true) || \
	(is_file(*cmd_temp) == true))
	{
		*cmd_temp = (*cmd_temp)->next;
		return (true);
	}
	return (false);
}

void	ft_close_pipefds(int fd[2], int old_read_fd)
{
	if (old_read_fd != 0)
		close(old_read_fd);
	if (fd[1] != 0) //verificar melhor essa condição
		close(fd[1]); 
	if (fd[0] != 0)
		close(fd[0]);
}

int	handle_pipe_and_redir(t_minishell *shell, t_cmd *commands)
{
	int		fd[2];
	int		old_read_fd;
	int		i;
	pid_t	pid;
	t_cmd	*cmd_temp;
	pid_t	last_child_pid = -1;
	int		status;


	i = 0;
	cmd_temp = commands;
	old_read_fd = 0;
	while (cmd_temp != NULL)
	{
		if (check_and_advance_cmd(&cmd_temp, &i))
			continue ;
		//printf("cmd_temp->cmd: %s\n", cmd_temp->cmd);
		create_pipe(fd);
		pid = create_child_process();
		if (pid == 0)
			manage_child(shell, cmd_temp, old_read_fd, fd);
		else
		{
			manage_parent(pid, &old_read_fd, fd, &status);
			last_child_pid = pid;
		}
		cmd_temp = cmd_temp->next;
	}
	if (last_child_pid != -1)
	{
		waitpid(last_child_pid, &status, 0); // Espera especificamente pelo último filho
	}
	shell->exit_status = WEXITSTATUS(status);
	ft_close_pipefds(fd, old_read_fd);
	return (0);
}
