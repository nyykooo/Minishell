/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_analyze.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncampbel <ncampbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 17:08:53 by ncampbel          #+#    #+#             */
/*   Updated: 2024/08/14 20:52:55 by ncampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../libs/headers.h"

static void	analyze_commands(t_minishell *shell)
{
	t_cmd	*temp;

	if (shell->commands == NULL)
		return ;
	shell->commands->prev = NULL;
	temp = shell->commands;
	while (temp)
	{
		ft_analyze_arguments(shell, temp);
		temp = temp->next;
	}
}

void	ft_analyze_tokens(t_token *tokens, t_minishell *shell)
{
	while (tokens != NULL)
	{
		if (tokens->type == T_COMMAND || tokens->type == T_EQUAL
			|| (tokens->type >= T_RTRUNC) || (tokens->type == T_ARG \
			&& tokens->prev->prev \
			&& tokens->prev->prev->type == T_LAPEND))
		{
			if (tokens->type >= T_RTRUNC)
				shell->n_pipe++;
			else
				shell->n_cmd++;
			ft_create_command(tokens, shell);
		}
		tokens = tokens->next;
	}
	analyze_commands(shell);
	return ;
}
