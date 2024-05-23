/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncampbel <ncampbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 16:59:28 by brunhenr          #+#    #+#             */
/*   Updated: 2024/05/23 22:25:26 by ncampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	skip_and_find_next_word(const char *s, char c, int *i, int *j)
{
	while (s[*i] == c && s[*i] != '\0')
		(*i)++;
	*j = *i;
	while (s[*i] != c && s[*i] != '\0')
		(*i)++;
}

int	count_words(const char *s, char c)
{
	int	count;
	int	i;
	int	j;

	count = 0;
	i = 0;
	j = 0;
	while (s[i] != '\0')
	{
		skip_and_find_next_word(s, c, &i, &j);
		if (i > j)
			count++;
	}
	return (count);
}

int	allocate_words(const char *s, char **strings, char c)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	k = 0;
	while (s[i] != '\0')
	{
		skip_and_find_next_word(s, c, &i, &j);
		if (i > j)
		{
			strings[k] = malloc(sizeof(char) * (i - j) + 1);
			if (strings[k] == NULL)
			{
				while (k >= 0)
					free(strings[k--]);
				free(strings);
				return (1);
			}
			k++;
		}
	}
	return (0);
}

void	copy_to_string(const char *s, char **string, char c)
{
	int	i;
	int	j;
	int	k;
	int	p;

	i = 0;
	j = 0;
	k = 0;
	p = 0;
	while (s[i] != '\0')
	{
		skip_and_find_next_word(s, c, &i, &j);
		if (i > j)
		{
			p = 0;
			while (j < i)
				string[k][p++] = s[j++];
			string[k][p] = '\0';
			k++;
		}
	}
}

char	**ft_split(char const *s, char c)
{
	char	**string;
	int		count;
	int		control;

	if (s == NULL)
		return (NULL);
	count = 0;
	control = 0;
	count = count_words(s, c) + 1;
	string = malloc(sizeof(char *) * count);
	if (string == NULL)
		return (NULL);
	string[count - 1] = NULL;
	control = allocate_words(s, string, c);
	if (control == 1)
		return (NULL);
	copy_to_string(s, string, c);
	return (string);
}

/*int	main()
{
	int	i = 0;
	char	*str;
	char	**strings;

	str = "-6 -67 -61 -38 9 -16 -16 32 56 16 ";
	strings = ft_split(str, ' ');
	while (strings[i] != NULL)
	{
		printf("split[%d]:%s\n", i, strings[i]);
		i++;
	}
	return (0);
}*/
