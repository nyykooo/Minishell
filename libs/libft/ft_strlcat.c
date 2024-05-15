/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncampbel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 16:22:19 by ncampbel          #+#    #+#             */
/*   Updated: 2023/10/23 18:24:38 by ncampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	j;
	size_t	i;
	size_t	dst_l;

	dst_l = ft_strlen(dst);
	i = ft_strlen(dst);
	if (size == 0 || size <= i)
		return (ft_strlen(src) + size);
	j = 0;
	while (src[j] != 0 && i < size - 1)
		dst[i++] = src[j++];
	dst[i] = '\0';
	return (dst_l + ft_strlen(src));
}
