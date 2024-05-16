/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncampbel <ncampbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 14:28:12 by ncampbel          #+#    #+#             */
/*   Updated: 2024/05/16 15:46:19 by ncampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_count_words(char const *s, char c)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c && s[i + 1] != '\0')
		{
			count++;
			while (s[i] != c && s[i] != '\0')
				i++;
		}
		else
			i++;
	}
	return (count);
}

static char	ft_wordlen(const char *str, char sep)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != sep)
		i++;
	return (i);
}

char	**ft_split(const char *s, char c)
{
	char	**list;
	int		position;
	int		words;

	words = ft_count_words(s, c);
	list = (char **)malloc((words + 1) * sizeof(char *));
	if (!list)
		return (NULL);
	list[words] = 0;
	position = 0;
	while (words > 0)
	{
		while (*s == c)
			s++;
		list[position] = ft_substr(s, 0, ft_wordlen(s, c));
		if (!list)
			break ;
		s += ft_wordlen(s, c);
		position++;
		words--;
	}
	return (list);
}
