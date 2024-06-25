/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncampbel <ncampbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 11:09:28 by ncampbel          #+#    #+#             */
/*   Updated: 2024/06/25 12:10:27 by ncampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	if (size != 0)
	{
		while (src[i] != 0 && i <= size - 1)
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (ft_strlen(src));
}

int	ft_arraylcpy(char **dst, const char **src, int size)
{
	int	i;

	i = -1;
	if (size != 0)
	{
		while (src[++i] != 0 && i < size)
			dst[i] = ft_strdup(src[i]);
		dst[i] = 0;
	}
	return (ft_array_len((char **)src));
}
