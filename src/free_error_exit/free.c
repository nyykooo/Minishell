/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncampbel <ncampbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 23:25:35 by ncampbel          #+#    #+#             */
/*   Updated: 2024/05/30 19:49:59 by ncampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libs/headers.h"

void	free_shell(t_minishell *shell)
{
	if (shell->envvars != NULL)
		free(shell->envvars);
	if (shell->tokens != NULL)
		free_tokens(shell->tokens);
	if (shell->input != NULL)
		free(shell->input);
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
}

void	free_array(char **array)
{
	int i;

	i = 0;
	while (array[i] != NULL)
		free(array[i++]);
	free(array);
}