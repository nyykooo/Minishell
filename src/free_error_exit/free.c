/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunhenr <brunhenr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 23:25:35 by ncampbel          #+#    #+#             */
/*   Updated: 2024/07/16 16:45:36 by brunhenr         ###   ########.fr       */
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

void	free_commands(t_cmd *commands)
{
	t_cmd *tmp;
	t_arg *tmp_arg;

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

void	free_shell(t_minishell *shell)
{
	rl_clear_history();
	clear_history();
	if (shell->envvars != NULL)
		free_var(shell->envvars);
	if (shell->tokens != NULL)
		free_tokens(shell->tokens);
	if (shell->input != NULL)
		free(shell->input);
	if (shell->commands != NULL)
		free_commands(shell->commands);
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
// as there is no more t_tokens, everywere this function was being used should be updated to free_array

void	free_tokens(t_token *tokens)
{
	t_token *tmp;
	
	
	while (tokens)
	{
		tmp = tokens;
		tokens = tokens->next;
		free(tmp->content);
		free(tmp);
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
		free(current->name);
		free(current->value);
		free(current);
		current = next;
	}
}