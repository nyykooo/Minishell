/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_functions2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunhenr <brunhenr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 17:31:55 by ncampbel          #+#    #+#             */
/*   Updated: 2024/08/09 11:50:52 by brunhenr         ###   ########.fr       */
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

void	ft_free_arguments(t_arg **arguments)
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
