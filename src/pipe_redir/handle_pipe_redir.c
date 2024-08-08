/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pipe_redir.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncampbel <ncampbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 15:59:53 by brunhenr          #+#    #+#             */
/*   Updated: 2024/08/08 20:12:51 by ncampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libs/headers.h"

void	create_pipe(int fd[2])
{
	if (pipe(fd) == -1)
	{
		perror("pipe");
		exit(1);
	}
}

static void	ft_close_pipefds(int fd[2], int old_read_fd)
{
	if (old_read_fd != 0)
		close(old_read_fd);
	if (fd[1] != 0)
		close(fd[1]);
	if (fd[0] != 0)
		close(fd[0]);
}

static void	analyze_status(int status, t_minishell *shell)
{
	if (WIFEXITED(status))
		shell->exit_status = WEXITSTATUS(status);
	if (WIFSIGNALED(status) || WIFSTOPPED(status))
	{
		if (WTERMSIG(status) == SIGQUIT)
		{
			shell->exit_status = 131;
			printf("Quit\n");
		}
		else if (WTERMSIG(status) == SIGINT)
		{
			shell->exit_status = 130;
			printf("\n");
		}
	}
}

static void	ft_wait_all_children(t_minishell *shell)
{
	int	waitpid_return;
	int	status;

	waitpid_return = 0;
	while (waitpid_return != -1)
	{
		waitpid_return = waitpid(-1, &status, 0);
		if (waitpid_return > 0)
		{
			if (WIFEXITED(status))
				continue ;
			else if (WIFSIGNALED(status))
			{
				if (WTERMSIG(status) == SIGQUIT)
					shell->exit_status = 131;
				else if (WTERMSIG(status) == SIGINT)
				{
					shell->exit_status = 130;
					printf("\n");
				}
			}
		}
	}
}

void	handle_pipe_and_redir(t_minishell *shell, t_cmd *commands)
{
	int		fd[2];
	int		old_read_fd;
	int		status;

	ignore_some_signals();
	old_read_fd = 0;
	status = ft_pipe_redir_loop(shell, commands, fd, old_read_fd);
	ft_wait_all_children(shell);
	analyze_status(status, shell);
	ft_close_pipefds(fd, old_read_fd);
	config_signals(0);
}
