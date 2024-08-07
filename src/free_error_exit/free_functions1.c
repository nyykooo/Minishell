/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_functions1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncampbel <ncampbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 23:25:35 by ncampbel          #+#    #+#             */
/*   Updated: 2024/08/07 19:52:37 by ncampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libs/headers.h"

void	free_commands(t_cmd *commands)
{
	t_cmd	*tmp;
	t_arg	*tmp_arg;

	while (commands)
	{
		if (commands->cmd != NULL)
			free(commands->cmd);
		while (commands->arguments)
		{
			tmp_arg = commands->arguments;
			commands->arguments = commands->arguments->next;
			free(tmp_arg->arg);
			free(tmp_arg);
		}
		tmp = commands;
		commands = commands->next;
		free(tmp);
	}
}

void	close_survivors_fds(void)
{
	int	fd;

	fd = 3;
	while (1)
	{
		if (close(fd) == -1 && errno == EBADF)
			break ;
		fd++;
	}
}

void	free_shell(t_minishell *shell)
{
	rl_clear_history();
	if (shell->envvars != NULL)
		free_var(shell->envvars);
	if (shell->tokens != NULL)
		free_tokens(shell->tokens);
	if (shell->input != NULL)
		free(shell->input);
	if (shell->commands != NULL)
		free_commands(shell->commands);
	close_survivors_fds();
}

void	free_arguments(t_arg **arguments)
{
	int	i;

	i = 0;
	while (arguments[i] != NULL)
	{
		if (arguments[i]->arg != NULL)
			free(arguments[i]->arg);
		free(arguments[i]);
		i++;
	}
}

void	free_tokens(t_token *tokens)
{
	t_token	*tmp;

	while (tokens)
	{
		tmp = tokens;
		tokens = tokens->next;
		free(tmp->content);
		free(tmp);
	}
}
