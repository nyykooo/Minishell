/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncampbel <ncampbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 13:13:40 by ncampbel          #+#    #+#             */
/*   Updated: 2024/08/15 17:50:36 by ncampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libs/headers.h"

static bool	look_for_flag(t_arg *argument)
{
	int		j;

	j = 0;
	if (argument->arg == NULL)
		return (false);
	if (argument->arg[j] == '-')
	{
		j++;
		while (argument->arg[j] == 'n')
			j++;
		if (argument->arg[j] == '\0' && j > 1)
		{
			argument = argument->next;
			return (true);
		}
		else
			return (false);
	}
	else
		return (false);
}

void	ft_handle_echo(t_cmd *command)
{
	bool	flag;
	bool	not_flag;
	t_arg	*temp_arg;

	flag = false;
	not_flag = false;
	temp_arg = command->arguments;
	while (temp_arg != NULL)
	{
		if (look_for_flag(temp_arg) && !not_flag)
			flag = true;
		else
		{
			printf("%s", temp_arg->arg);
			if (temp_arg->next != NULL && !temp_arg->next->expanded)
				printf(" ");
			not_flag = true;
		}
		temp_arg = temp_arg->next;
	}
	if (!flag)
		printf("\n");
	command->shell->exit_status = 0;
}
