/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunhenr <brunhenr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 10:43:27 by ncampbel          #+#    #+#             */
/*   Updated: 2024/08/07 13:17:15 by brunhenr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	size_t	len;
	size_t	i;
	char	*new;

	i = 0;
	if (!s)
		return (NULL);
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
