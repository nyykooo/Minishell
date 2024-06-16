/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncampbel <ncampbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 13:13:40 by ncampbel          #+#    #+#             */
/*   Updated: 2024/06/16 22:45:05 by ncampbel         ###   ########.fr       */
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
		if (argument->arg[j] == '\0')
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

void	handle_echo(t_cmd *command)
{
	bool	flag;
	t_arg	*temp_arg;

	flag = false;
	temp_arg = command->arguments;
	// printf("%d\n", ft_argsize(command->arguments));
	while (temp_arg != NULL)
	{
		if (look_for_flag(temp_arg))
			flag = true;
		else
		{
			printf("%s", temp_arg->arg);
			if (temp_arg->next != NULL && !temp_arg->next->expanded) // confirmar se o expanded é o primeiro ou segundo arg
				printf(" ");
			temp_arg = temp_arg->next;
		}
	}
	if (!flag)
		printf("\n");
}
