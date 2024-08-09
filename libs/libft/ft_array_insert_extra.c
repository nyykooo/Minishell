/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_array_insert_extra.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunhenr <brunhenr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 00:50:32 by ncampbel          #+#    #+#             */
/*   Updated: 2024/08/09 11:31:11 by brunhenr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_array_insert_extra(char **array, char *insert, \
char *extra, int index)
{
	char	**new_array;
	int		i;
	int		size;

	i = index;
	if (insert == NULL)
		size = ft_array_len(array) + 2;
	else
		size = ft_array_len(array) + 3;
	new_array = (char **)malloc(sizeof(char *) * size);
	if (!new_array)
		return (NULL);
	ft_arraylcpy(new_array, (const char **)array, index);
	new_array[i++] = ft_strcutstr(array[index++], extra);
	new_array[i++] = ft_strdup(extra);
	if (insert != NULL && insert[0] != '\0')
		new_array[i++] = ft_strdup(insert);
	while (array[index])
	{
		new_array[i] = ft_strdup(array[index++]);
		i++;
	}
	ft_free_array(array);
	return (new_array);
}
