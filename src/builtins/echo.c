/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncampbel <ncampbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 13:13:40 by ncampbel          #+#    #+#             */
/*   Updated: 2024/06/09 10:10:42 by ncampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libs/headers.h"


static bool look_for_flag(t_arg **argument, int *i)
{
	int		j;

	j = 0;
	if (argument[*i]->arg == NULL)
		return (false);
	if (argument[*i]->arg[j] == '-')
	{
		j++;
		while (argument[*i]->arg[j] == 'n' && argument[*i]->arg[j] != '\0')
			j++;
		if (argument[*i]->arg[j] == '\0')
		{
			(*i)++;
			return (true);
		}
		else
			return (false);
	}
	else
		return false;
}

void handle_echo(t_token **tokens)
{
	int i;
	bool flag;

	i = 1;
	flag = false;
	while (tokens[0]->argument[i]->arg != NULL)
	{
		if(look_for_flag(tokens[0]->argument, &i))
			flag = true;
		else
		{	
			printf("%s", tokens[0]->argument[i]->arg);
			if (tokens[0]->argument[i + 1] != NULL)
				printf(" ");
			i++;
		}
	}
	if (!flag)
		printf("\n");
}
