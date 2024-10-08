/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunhenr <brunhenr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 17:00:04 by brunhenr          #+#    #+#             */
/*   Updated: 2024/08/09 11:35:01 by brunhenr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libs/headers.h"

void	ft_redefine_child_signals(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

void	ft_ignore_some_signals(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

void	ft_handle_sigint(int sig)
{
	t_minishell	*shell;

	shell = ft_get_shell();
	if (sig == SIGINT)
	{
		printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		shell->exit_status = 130;
	}
}

static void	hd_ft_handle_sigint(int signal)
{
	if (signal == SIGINT)
	{
		g_sig = SIGINT;
		close(STDIN_FILENO);
	}
}

void	ft_config_signals(int process_type)
{
	struct sigaction	sigint;
	struct sigaction	sigquit;

	sigemptyset(&sigint.sa_mask);
	sigemptyset(&sigquit.sa_mask);
	sigquit.sa_handler = SIG_IGN;
	if (process_type == 0)
		sigint.sa_handler = ft_handle_sigint;
	else
		sigint.sa_handler = hd_ft_handle_sigint;
	sigint.sa_flags = 0;
	sigquit.sa_flags = 0;
	sigaction(SIGINT, &sigint, NULL);
	sigaction(SIGQUIT, &sigquit, NULL);
}
