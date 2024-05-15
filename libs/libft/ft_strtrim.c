/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncampbel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 15:32:06 by ncampbel          #+#    #+#             */
/*   Updated: 2023/10/23 17:41:59 by ncampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(const char *s1, const char *set)
{
	size_t	i;
	size_t	j;
	size_t	size;

	j = ft_strlen(s1);
	i = 0;
	while (s1[i] != 0 && ft_strchr(set, s1[i]) != 0)
		i++;
	while (j && ft_strchr(set, s1[j]) != 0)
		j--;
	size = ft_strlen(s1) - (ft_strlen(s1) - j) - i + 1;
	return (ft_substr(s1, i, size));
}
