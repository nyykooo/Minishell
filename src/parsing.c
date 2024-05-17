/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunhenr <brunhenr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 14:13:05 by ncampbel          #+#    #+#             */
/*   Updated: 2024/05/17 13:46:18 by brunhenr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libs/headers.h"

static char *deal_quotes(char **input)
{
	int i;

	i = 0;
	if (*input[i] == '"')
	{
		(*input)++;
		while ((**input) != '"')
		{
			i++;
			(*input)++;
		}
	}
	else if (*input[i] == '\'')
	{
		(*input)++;
		while ((**input) != '\'')
		{
			i++;
			(*input)++;
		}
	}
	return (ft_substr(*input - i, 0, i));
}

static char *deal_normal(char **input)
{
	int i;

	i = 0;
	while (**input != ' ' && **input != '\0')
	{
		*input++;
		i++;
	}
	return (ft_substr(*input - i, 0, i));
}

static int new_commands(const char *input)
{
	int count;

	count = 0;
	while (*input != '\0')
	{
		while (*input == ' ')
			input++;
		if (*input != '\0')
		{
			count++;
			while (*input != ' ' && *input != '\0')
			{
				if (*input == '"' || *input == '\'')
				{
					if (*input == '"')
						while (*input != '"' && *input != '\0')
							input++;
					while (*input != '\'' && *input != '\0')
						input++;
					if (*input == '\0')
						return (-1);
				}
				input++;
			}
		}
	}
	return (count);
}

// static int	count_commands(const char *input)
// {
// 	int	i;
// 	int	count;
	
// 	i = 0;
// 	count = 0;
// 	while (input[i] != '\0')
// 	{
// 		while (input[i] == ' ')
// 			i++;
// 		if (input[i] != '\0')
// 			count++;
// 		if (input[i] == '"' || input[i] == '\'')
// 		{
// 			if (input[i] == '"')
// 				while (input[i] != '"' && input[i] != '\0')
// 					i++;
// 			while (input[i] != '\'' && input[i] != '\0')
// 				i++;
// 			if (input[i] == '\0')
// 				return (-1);
// 		}
// 		i++;
// 	}
// 	return (count);
// }

char **mega_parsing(char *input)
{
	char **list;
	int position;
	int n_commands;

	n_commands = new_commands(input);
	if (n_commands == -1)
		return (NULL);
	list = (char **)malloc((n_commands + 1) * sizeof(char *));
	if (!list)
		return (NULL);
	list[n_commands] = NULL;
	position = 0;
	while (position < n_commands)
	{
		while (*input == ' ')
			input++;
		if (*input == '"' || *input == '\'')
			list[position] = deal_quotes(&input);			
		else
			list[position] = deal_normal(&input);
		position++;
	}
	return (list);
}
