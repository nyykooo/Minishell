/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_functions1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncampbel <ncampbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 23:25:35 by ncampbel          #+#    #+#             */
/*   Updated: 2024/08/14 20:52:43 by ncampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libs/headers.h"

void	ft_close_survivors_fds(void)
{
	int	fd;
	int	i;

	fd = 3;
	i = 3;
	while (i < 1024)
	{
		close(fd);
		fd++;
		i++;
	}
}

void	ft_free_shell(t_minishell *shell)
{
	rl_clear_history();
	if (shell->envvars != NULL)
		ft_free_var(shell->envvars);
	if (shell->tokens != NULL)
		ft_free_tokens(shell->tokens);
	if (shell->input != NULL)
		free(shell->input);
	if (shell->commands != NULL)
		ft_free_commands(shell->commands);
	ft_close_survivors_fds();
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

void	ft_free_tokens(t_token *tokens)
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
