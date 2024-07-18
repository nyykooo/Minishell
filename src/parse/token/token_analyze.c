/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_analyze.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncampbel <ncampbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 17:08:53 by ncampbel          #+#    #+#             */
/*   Updated: 2024/07/06 17:37:31 by ncampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../libs/headers.h"

// analyze_tokens is a function that analyzes the tokens and creates the commands

static void analyze_commands(t_minishell *shell)
{
	t_cmd *temp;
	
	temp = shell->commands;
	while (temp)
	{
		analyze_arguments(shell, temp);
		temp = temp->next;
	}
}

void	analyze_tokens(t_token *tokens, t_minishell *shell)
{
	while (tokens != NULL)
	{
		if (tokens->type == T_COMMAND || tokens->type == T_EQUAL
			|| (tokens->type >= T_RTRUNC)) // checks if token is a command, a pipe or a executable
		{
			if (tokens->type >= T_RTRUNC)
				shell->n_pipe++;
			else
				shell->n_cmd++;
			create_command(tokens, shell); // create_command is a function that creates a command structure
		}
		tokens = tokens->next;
	}
	analyze_commands(shell); // analyze_commands is a function that analyzes the command's arguments
	return ;
}
