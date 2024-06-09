/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncampbel <ncampbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 23:25:35 by ncampbel          #+#    #+#             */
/*   Updated: 2024/06/08 19:51:16 by ncampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libs/headers.h"

void	free_shell(t_minishell *shell)
{
	if (shell->envvars != NULL)
	{
		free_var(shell->envvars);
		free(shell->envvars);
	}
	if (shell->tokens != NULL)
		free_tokens(shell->tokens);
	if (shell->input != NULL)
		free(shell->input);
}

void	free_arguments(t_arg **arguments)
{
	int i;

	i = 0;
	while (arguments[i] != NULL)
	{
		if (arguments[i]->arg != NULL)
			free(arguments[i]->arg);
		free(arguments[i]);
		i++;
	}
}

void	free_tokens(t_token **tokens)
{
	int i;

	i = 0;
	while (tokens[i] != NULL)
	{
		if (tokens[i]->argument != NULL)
		{
			free_arguments(tokens[i]->argument);
			free(tokens[i]->cmd);
		}
		free(tokens[i]);
		i++;
	}
}

void	free_array(char **array)
{
	int i;

	i = 0;
	while (array[i] != NULL)
		free(array[i++]);
	free(array);
}

void	free_var(t_var *head)
{
	t_var	*current;
	t_var	*next;

	current = head;
	while (current)
	{
		next = current->next;
		free(current->content);
		free(current);
		current = next;
	}
}