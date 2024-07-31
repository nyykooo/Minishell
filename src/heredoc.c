/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunhenr <brunhenr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 09:52:35 by brunhenr          #+#    #+#             */
/*   Updated: 2024/07/16 17:56:03 by brunhenr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libs/headers.h"

void	write_line_to_pipe(char *line, int fd[2])
{
	write(fd[1], line, ft_strlen(line));
	write(fd[1], "\n", 1);
	free(line);
}

void	loop_heredoc(t_cmd *current, int fd[2], t_minishell *shell)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (g_sig == SIGINT)
		{
			write(STDOUT_FILENO, "\n", 1);
			g_sig = 0;
			exit (8);
		}
		if (!line)
		{
			write (STDERR_FILENO, "-minishell: Warning: here-document "
				"delimited by end-of-file\n", 60);
			exit (10);
		}
		if (current->next->cmd && ft_strcmp(line, current->next->cmd) == 0)
		{
			free(line);
			break ;
		}
		expand_dolar(&line, shell);
		write_line_to_pipe(line, fd);
	}
}


int	fork_and_execute_heredoc(t_cmd *current, int fd[2], t_minishell *shell)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(1);
	}
	if (pid == 0)
	{
		config_signals(1);
		loop_heredoc(current, fd, shell);
		close(fd[0]);
		close(fd[1]);
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
			if (current->here_doc_fd > 2)
				close(current->here_doc_fd);
			create_pipe(fd);
			pid = fork_and_execute_heredoc(current, fd, shell);
			waitpid(pid, &status, 0);
			sigaction(SIGINT, sa_original, NULL);
			if (fd[1] > 2)
				close(fd[1]);
			if (current->prev)
				current->prev->here_doc_fd = fd[0];
			//close(fd[0]);
		}
		current = current->next;
	}
	return (status);
}

void	config_ignore_sigint(struct sigaction *sa_original)
{
	struct sigaction	sa_ignore;

	sa_ignore.sa_handler = SIG_IGN;
	sigemptyset(&sa_ignore.sa_mask);
	sa_ignore.sa_flags = 0;
	sigaction(SIGINT, &sa_ignore, sa_original);
}

void	initialize_heredoc(struct termios *term, struct sigaction *sa_original)
{
	config_ignore_sigint(sa_original);
	tcgetattr(STDIN_FILENO, term);
}

void	finalize_heredoc(struct termios *term, struct sigaction *sa_original)
{
	if (sigaction(SIGINT, sa_original, NULL) == -1)
	{
		perror("sigaction");
		exit(1);
	}
	tcsetattr(STDIN_FILENO, TCSANOW, term);
}


int	heredoc(t_minishell *shell)
{
	struct termios		term;
	struct sigaction	sa_original;
	int					status;

	initialize_heredoc(&term, &sa_original);
	status = process_heredoc_cmds(shell, &sa_original);
	finalize_heredoc(&term, &sa_original);
	return (status);
}
