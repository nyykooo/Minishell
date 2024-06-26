/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncampbel <ncampbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 10:43:27 by ncampbel          #+#    #+#             */
/*   Updated: 2024/05/30 20:14:37 by ncampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	size_t	len;
	size_t	i;
	char	*new;

	i = 0;
	len = ft_strlen(s);
	new = (char *)malloc(len * sizeof(char) + 1);
	if (new == NULL)
		return (NULL);
	while (s[i] != 0)
	{
		new[i] = s[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}
