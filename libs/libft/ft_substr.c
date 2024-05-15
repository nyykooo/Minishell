/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncampbel <ncampbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 15:53:22 by ncampbel          #+#    #+#             */
/*   Updated: 2024/03/30 17:20:08 by ncampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	size;
	char	*new;

	i = 0;
	if (s[0] == '\0' || len == 0 || start >= ft_strlen(s))
		return (NULL);
	if (len > ft_strlen(s + start))
		size = ft_strlen(s + start);
	else
		size = len;
	new = (char *)malloc(size + 1);
	if (!(new))
		return (NULL);
	while (i < len && s[start] != '\0')
		new[i++] = s[start++];
	new[i] = '\0';
	return (new);
}
