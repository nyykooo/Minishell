/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncampbel <ncampbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 13:30:00 by ncampbel          #+#    #+#             */
/*   Updated: 2024/04/10 18:14:12 by ncampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*ns;
	size_t			i;

	ns = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		if (ns[i] == (unsigned char) c)
			return ((void *)s);
		i++;
	}
	return (NULL);
}
