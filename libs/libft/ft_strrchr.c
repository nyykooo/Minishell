/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncampbel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 10:36:26 by ncampbel          #+#    #+#             */
/*   Updated: 2023/10/09 13:33:08 by ncampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	i;
	int	j;

	i = 0;
	if ((char)c == '\0')
		return ((char *)&s[ft_strlen(s)]);
	while (s[i] != '\0')
	{
		j = 1;
		if (s[i] == (char)c)
		{
			while (s[i + j] != '\0' && s[i + j] != (char)c)
				j++;
			if (s[i + j] == '\0')
				return ((char *)&s[i]);
		}
		i++;
	}
	return (NULL);
}
