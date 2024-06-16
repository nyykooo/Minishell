/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_array_insert_extra.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncampbel <ncampbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 00:50:32 by ncampbel          #+#    #+#             */
/*   Updated: 2024/06/16 20:38:10 by ncampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char **ft_array_insert_extra(char **array, char *insert, char *extra, int index)
{
	char **new_array;
	int i;
	int j;

	i = -1;
	j = -1;
	new_array = (char **)malloc(sizeof(char *) * (ft_array_len(array) + 3)); // +3 for the extra, insert and the NULL
	if (!new_array)
		return (NULL);
	while (array[++j] && ++i < index)
		new_array[i] = ft_strdup(array[j]);
	new_array[i] = ft_strdup(extra);
	new_array[i] = ft_strdup(insert);
	while (array[j])
		new_array[++i] = ft_strdup(array[++j]);
	new_array[i] = NULL;
	free_array(array);
	return (new_array);
}
