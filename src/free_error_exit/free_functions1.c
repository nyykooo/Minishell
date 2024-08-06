/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_functions1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncampbel <ncampbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 23:25:35 by ncampbel          #+#    #+#             */
/*   Updated: 2024/08/06 17:34:01 by ncampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libs/headers.h"

static void	close_survivors_fds(void)
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
// as there is no more t_tokens, everywere this function was being used should be updated to free_array

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

void	free_array(char **array)
{
	int	i;

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
