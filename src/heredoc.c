/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunhenr <brunhenr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 09:52:35 by brunhenr          #+#    #+#             */
/*   Updated: 2024/07/16 13:56:21 by brunhenr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libs/headers.h"

void	loop_heredoc(t_cmd *current, int fd[2])
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			if (g_sig != SIGINT)
			{
				write (STDERR_FILENO, "-minishell: Warning: here-document delimited by end-of-file\n", 60);
				exit (10);
			}
			write(STDOUT_FILENO, "\n", 1);
			g_sig = 0;
			exit (8);
		}
		if (g_sig == SIGINT)
		{
			write(STDOUT_FILENO, "\n", 1);
			g_sig = 0;
			exit (8);
		}
		if (ft_strncmp(line, current->next->cmd, ft_strlen(current->next->cmd)) == 0)
		{
			free(line);
			break;
		}
		write(fd[1], line, ft_strlen(line));
		write(fd[1], "\n", 1);
		free(line);
	}
}

void	actual_heredoc(t_cmd *current, int fd[2])
{
	config_signals(1);
	loop_heredoc(current, fd);
	close(fd[0]);
	close(fd[1]);
	exit(0); //colocar ft de exit
}
void	config_ignore_sigint(struct sigaction *sa_original)
{
	struct sigaction	sa_ignore;
	sa_ignore.sa_handler = SIG_IGN;
	sigemptyset(&sa_ignore.sa_mask);
	sa_ignore.sa_flags = 0;
	sigaction(SIGINT, &sa_ignore, sa_original);
}

int	fork_and_execute_heredoc(t_cmd *current, int fd[2])
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(1); // Considerar criar uma função de saída que limpe recursos
	}
	if (pid == 0)
        actual_heredoc(current, fd);
	return (pid);
}

int	heredoc(t_minishell *shell)
{
	struct termios		term;
	t_cmd				*current;
	int					fd[2];
	pid_t				pid;
	int					status;
	struct sigaction	sa_original;

	config_ignore_sigint(&sa_original);
	status = 0;
	current = shell->commands;
	tcgetattr(STDIN_FILENO, &term);
	while (current)
	{
		if (current->type == T_LAPEND)
		{
			if (current->here_doc_fd > 2)
				close(current->here_doc_fd);
			create_pipe(fd);
			pid = fork_and_execute_heredoc(current, fd);
			waitpid(pid, &status, 0);
			sigaction(SIGINT, &sa_original, NULL);
			if (fd[1] > 2)
				close(fd[1]);
			if (current->prev)
				current->prev->here_doc_fd = fd[0];
		}
		tcsetattr(STDIN_FILENO, TCSANOW, &term);
		current = current->next;
	}
	return (status);
}
