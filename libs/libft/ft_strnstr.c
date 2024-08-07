/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunhenr <brunhenr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 16:38:12 by ncampbel          #+#    #+#             */
/*   Updated: 2024/08/07 13:22:26 by brunhenr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (little[i] == 0)
		return ((char *)big);
	while (big[i] != 0 && i < len)
	{
		j = 0;
		while (big[i + j] != 0 && big[i + j] == little[j] && i + j < len)
			j++;
		if (little[j] == 0)
			return ((char *)big + i);
		i++;
	}
	return (NULL);
}

char	*ft_strcutstr(const char *big, const char *little)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (little[i] == 0)
		return ((char *)big);
	while (big[i] != 0)
	{
		j = 0;
		while (big[i + j] != 0 && big[i + j] == little[j])
			j++;
		if (little[j] == 0)
			return (ft_substr(big, 0, i));
		i++;
	}
	return (NULL);
}
