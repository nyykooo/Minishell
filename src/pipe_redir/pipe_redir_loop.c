/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_redir_loop.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunhenr <brunhenr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 16:32:13 by brunhenr          #+#    #+#             */
/*   Updated: 2024/08/05 17:20:09 by brunhenr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libs/headers.h"

static void	manage_parent(int fd[2], int *old_read_fd, pid_t pid, \
pid_t *last_child_pid)
{
	if (*old_read_fd != 0)
		close(*old_read_fd);
	*old_read_fd = fd[0];
	close(fd[1]);
	*last_child_pid = pid;
}

static void	manage_child(t_minishell *shell, t_cmd *cmd_temp, \
int old_read_fd, int fd[2])
{
	int	in_fd;
	int	out_fd;
	int	has_pipe;

	redefine_child_signals();
	define_in_out_fd(cmd_temp, &in_fd, &out_fd);
	if (old_read_fd != 0)
	{
		dup2(old_read_fd, STDIN_FILENO);
		close(old_read_fd);
	}
	has_pipe = ft_has_pipe(cmd_temp);
	if (has_pipe)
	{
		ft_haspipe(in_fd, out_fd, fd[1], fd[0]);
		ft_exec(shell, cmd_temp);
	}
	else
	{
		ft_nopipe(in_fd, out_fd);
		ft_exec(shell, cmd_temp);
	}
}

static pid_t	create_child_process(void)
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

static bool	check_and_advance_cmd(t_cmd **cmd_temp, int *i)
{
	if ((is_pipe_or_redir(*cmd_temp, (*i)++) == true) || \
	(is_file(*cmd_temp) == true))
	{
		*cmd_temp = (*cmd_temp)->next;
		return (true);
	}
	return (false);
}

int	ft_pipe_redir_loop(t_minishell *shell, t_cmd *commands, \
int fd[2], int old_read_fd)
{
	t_cmd	*cmd_temp;
	pid_t	last_child_pid;
	int		status;
	int		i;
	int		pid;

	cmd_temp = commands;
	last_child_pid = -1;
	i = 0;
	status = 0;
	while (cmd_temp != NULL)
	{
		if (check_and_advance_cmd(&cmd_temp, &i))
			continue ;
		create_pipe(fd);
		pid = create_child_process();
		if (pid == 0)
			manage_child(shell, cmd_temp, old_read_fd, fd);
		else
			manage_parent(fd, &old_read_fd, pid, &last_child_pid);
		cmd_temp = cmd_temp->next;
	}
	if (last_child_pid != -1)
		waitpid(last_child_pid, &status, 0);
	return (status);
}
