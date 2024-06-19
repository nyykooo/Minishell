/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_to_array.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncampbel <ncampbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 16:43:59 by ncampbel          #+#    #+#             */
/*   Updated: 2024/06/19 16:44:12 by ncampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_to_array(t_cmd *command)
{
	int		i;
	char	**array;
	t_arg	*tmp;

	i = 0;
	tmp = command->arguments;
	while (tmp != NULL)
	{
		tmp = tmp->next;
		i++;
	}
	array = (char **)malloc(sizeof(char *) * (i + 1));
	i = 0;
	array[i++] = ft_strdup(command->cmd);
	while (command->arguments != NULL)
	{
		array[i++] = ft_strdup(command->arguments->arg);
		command->arguments = command->arguments->next;
	}
	array[i] = NULL;
	return (array);
}
