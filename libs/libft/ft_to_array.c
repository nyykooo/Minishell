/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_to_array.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncampbel <ncampbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 16:43:59 by ncampbel          #+#    #+#             */
/*   Updated: 2024/08/14 22:01:18 by ncampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**ft_first_arg(char *str)
{
	char	**array;

	array = (char **)malloc(sizeof(char *) * 2);
	array[0] = ft_strdup(str);
	array[1] = NULL;
	return (array);
}

char	**ft_to_array(t_cmd *command)
{
	int		i;
	char	**array;
	t_arg	*tmp;

	i = 0;
	if (command->arguments == NULL)
		return (ft_first_arg(command->cmd));
	tmp = command->arguments;
	while (tmp != NULL)
	{
		tmp = tmp->next;
		i++;
	}
	array = (char **)malloc(sizeof(char *) * (i + 2));
	i = 0;
	array[i++] = ft_strdup(command->cmd);
	tmp = command->arguments;
	while (tmp != NULL)
	{
		array[i++] = ft_strdup(tmp->arg);
		tmp = tmp->next;
	}
	array[i] = NULL;
	return (array);
}
