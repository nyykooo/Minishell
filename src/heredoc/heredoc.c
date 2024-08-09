/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunhenr <brunhenr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 09:52:35 by brunhenr          #+#    #+#             */
/*   Updated: 2024/08/09 12:44:32 by brunhenr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libs/headers.h"

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
