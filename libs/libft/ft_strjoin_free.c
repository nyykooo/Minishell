/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncampbel <ncampbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 16:29:01 by ncampbel          #+#    #+#             */
/*   Updated: 2024/07/22 11:04:56 by ncampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_free(char const *s1, char const *s2)
{
	size_t	len;
	size_t	i;
	size_t	j;
	char	*new;

	len = ft_strlen(s1) + ft_strlen(s2);
	new = (char *)malloc(len + 1);
	if (!new)
		return (NULL);
	i = 0;
	j = 0;
	if (s1)
		while (s1[j] != '\0')
			new[i++] = s1[j++];
	j = 0;
	if (s2)
		while (s2[j] != '\0')
			new[i++] = s2[j++];
	new[i] = '\0';
	if (s1)
		free((char *)s1);
	return (new);
}
