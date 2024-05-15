/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncampbel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 10:41:03 by ncampbel          #+#    #+#             */
/*   Updated: 2023/10/23 17:31:20 by ncampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	const char	*s;
	char		*d;

	s = src;
	d = dest;
	if (s < d)
	{
		while (n)
		{
			n--;
			d[n] = s[n];
		}
	}
	else if (s > d)
		ft_memcpy(dest, src, n);
	else if (s == d)
		return (d);
	return (dest);
}
