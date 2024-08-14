/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncampbel <ncampbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 08:29:20 by brunhenr          #+#    #+#             */
/*   Updated: 2024/08/14 16:55:56 by ncampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libs/headers.h"

void	close_fds(int fd[2])
{
	if (fd[0] > 2)
		close(fd[0]);
	if (fd[1] > 2)
		close(fd[1]);
}

static void	write_line_to_pipe(char *line, int fd[2])
{
	write(fd[1], line, ft_strlen(line));
	write(fd[1], "\n", 1);
	free(line);
}

static char	*loop_heredoc(t_cmd *current, int fd[2], t_minishell *shell)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (g_sig == SIGINT)
		{
			write(STDOUT_FILENO, "\n", 1);
			g_sig = 0;
			if (line)
				free(line);
			close_fds(fd);
			ft_free_shell(shell);
			exit (130);
		}
		if (!line)
		{
			write (STDERR_FILENO, HRDC_EOF, 60);
			break ;
		}
		if (current->next->cmd && ft_strcmp(line, current->next->cmd) == 0)
			break ;
		ft_expand_dolar(&line, shell);
		write_line_to_pipe(line, fd);
	}
	return (line);
}

static int	fork_and_execute_heredoc(t_cmd *current, int fd[2], \
t_minishell *shell)
{
	pid_t	pid;
	char	*line;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		ft_free_shell(shell);
		exit(1);
	}
	if (pid == 0)
	{
		ft_config_signals(1);
		line = loop_heredoc(current, fd, shell);
		if (line)
			free(line);
		ft_free_shell(shell);
		exit(0);
	}
	return (pid);
}

int	process_heredoc_cmds(t_minishell *shell, struct sigaction *sa_original)
{
	t_cmd	*current;
	int		fd[2];
	pid_t	pid;
	int		status;

	current = shell->commands;
	status = 0;
	while (current)
	{
		if (current->type == T_LAPEND)
		{
			ft_create_pipe(fd);
			pid = fork_and_execute_heredoc(current, fd, shell);
			waitpid(pid, &status, 0);
			if (status == 33280)
				break ;
			sigaction(SIGINT, sa_original, NULL);
			if (current->prev)
				current->prev->here_doc_fd = fd[0];
			if (fd[1] > 2)
				close(fd[1]);
		}
		current = current->next;
	}
	return (status);
}
