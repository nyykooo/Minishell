/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncampbel <ncampbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 14:28:12 by ncampbel          #+#    #+#             */
/*   Updated: 2024/05/18 00:13:43 by ncampbel         ###   ########.fr       */
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

static char *deal_quotes(const char *input)
{
	int i;

	i = 0;
	if (input[i] == '"')
	{
		(input)++;
		while ((*input) != '"')
		{
			i++;
			(input)++;
		}
	}
	else if (input[i] == '\'')
	{
		(input)++;
		while ((*input) != '\'')
		{
			i++;
			(input)++;
		}
	}
	return (ft_substr(input - i, 0, i));
}

static int quote_len(const char *input)
{
	int i;

	i = 0;
	if (input[i] == '"')
	{
		i++;
		while (input[i] != '"' && input[i] != '\0')
			i++;
	}
	else if (input[i] == '\'')
	{
		i++;
		while (input[i] != '\'' && input[i] != '\0')
			i++;
	}
	return (i);
}

static char	ft_wordlen(const char *str, char sep)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != sep)
		i++;
	return (i);
}

static int increment(const char *str, char sep)
{
	int	i;

	i = 0;
	if (str[i] == '\'' || str[i] == '"')
		i = quote_len(str);
	else 
		i = ft_wordlen(str, sep);
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
		if (*s == '\'' || *s == '"')
			list[position] = deal_quotes(s);
		else
			list[position] = ft_substr(s, 0, ft_wordlen(s, c));
		if (!list)
			break ;
		s += increment(s, c);
		position++;
		words--;
	}
	return (list);
}
