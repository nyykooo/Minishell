/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunhenr <brunhenr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 09:52:35 by brunhenr          #+#    #+#             */
/*   Updated: 2024/07/10 13:33:52 by brunhenr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libs/headers.h"

void	loop_heredoc(t_cmd *current, int fd[2])
{
	char	*line;

	//printf("entrou no loop do heredoc\n");
	line = readline("> ");
	if (!line)
		exit(0); //colocar ft de exit e tratar erro
	while (line)
	{
		if (ft_strncmp(line, current->next->cmd, ft_strlen(current->next->cmd)) == 0)
		{
			free(line);
			break ;
		}
		//aqui fazer expansões que sejam necessárias
		write(fd[1], line, ft_strlen(line));
		write(fd[1], "\n", 1);
		free(line);
		line = readline("> ");
		if (!line)
			exit(0); //colocar ft de exit e tratar erro
	}
}

void	actual_heredoc(t_cmd *current, int fd[2])
{
	loop_heredoc(current, fd);
	close(fd[0]);
	close(fd[1]);
	exit(0); //colocar ft de exit
}

void	heredoc(t_minishell *shell)
{
	struct termios	term;
	t_cmd			*current;
	int				fd[2];
	pid_t			pid;

	current = shell->commands;
	tcgetattr(STDIN_FILENO, &term);
	while (current)
	{
		if (current->type == T_LAPEND)
		{
			if (current->here_doc_fd > 2)
				close(current->here_doc_fd);
			if (pipe(fd) == -1)
			{
				perror("pipe"); //colocar ft de exit
				exit (1);
			}
			pid = fork();
			if (pid == -1)
			{
				perror("fork"); //colocar ft de exit
				exit(1);
			}
			if (pid == 0)
				actual_heredoc(current, fd);
			waitpid(pid, NULL, 0);
			if (fd[1] > 2)
				close(fd[1]);
			if (current->prev)
				current->prev->here_doc_fd = fd[0];
		}
		tcsetattr(STDIN_FILENO, TCSANOW, &term);
		current = current->next;
	}
}