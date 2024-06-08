/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunhenr <brunhenr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 23:25:35 by ncampbel          #+#    #+#             */
/*   Updated: 2024/06/07 15:22:05 by brunhenr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libs/headers.h"

void	free_list(t_var *head)
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

void	free_shell(t_minishell *shell)
{
	if (shell->envvars != NULL)
		free_list(shell->envvars);
	if (shell->tokens != NULL)
		free_tokens(shell->tokens);
	if (shell->input != NULL)
		free(shell->input);
	if (shell != NULL)
		free(shell);
}

void	free_tokens(t_token **tokens)
{
	int i;
	int j;

	i = 0;
	while (tokens[i] != NULL)
	{
		if (tokens[i]->argument != NULL)
		{
			j = -1;
			while (tokens[i]->argument[++j] != NULL)
				free(tokens[i]->argument[j]);
			free(tokens[i]->argument);
			free(tokens[i]->cmd);
		}
		free(tokens[i++]);
	}
	free(tokens);
}

void	free_array(char **array)
{
	int i;

	i = 0;
	while (array[i] != NULL)
		free(array[i++]);
	free(array);
}