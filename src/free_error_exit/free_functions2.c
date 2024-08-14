/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_functions2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncampbel <ncampbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 17:31:55 by ncampbel          #+#    #+#             */
/*   Updated: 2024/08/14 20:21:11 by ncampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libs/headers.h"

void	ft_free_list(t_var *head)
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

void	ft_free_commands(t_cmd *commands)
{
	t_cmd	*tmp;
	t_arg	*tmp_arg;

	while (commands)
	{
		while (commands->arguments)
		{
			tmp_arg = commands->arguments;
			commands->arguments = commands->arguments->next;
			free(tmp_arg->arg);
			free(tmp_arg);
		}
		if (commands->cmd != NULL)
			free(commands->cmd);
		tmp = commands;
		commands = commands->next;
		free(tmp);
	}
}

void	ft_free_array(char **array)
{
	int	i;

	i = 0;
	while (array[i] != NULL)
		free(array[i++]);
	free(array);
}

void	ft_free_var(t_var *head)
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
