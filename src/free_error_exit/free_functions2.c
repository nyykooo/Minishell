/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_functions2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncampbel <ncampbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 17:31:55 by ncampbel          #+#    #+#             */
/*   Updated: 2024/08/07 16:39:50 by ncampbel         ###   ########.fr       */
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
