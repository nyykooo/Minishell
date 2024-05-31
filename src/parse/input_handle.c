/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_handle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncampbel <ncampbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 13:37:26 by ncampbel          #+#    #+#             */
/*   Updated: 2024/05/30 09:21:28 by ncampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libs/headers.h"

static bool space_trim(char *input, char *temp)
{
	char	c;
	static int i = 0;
	static int j = 0;

	if (!input[i])
		return (false);
	while (input[i] && input[i] != '\'' && input[i] != '\"' && !ft_isspace(input[i]))
		temp[j++] = input[i++];
	if (input[i] == '\'' || input[i] == '\"')
	{
		c = input[i];
		temp[j++] = input[i++];
		while (input[i] && input[i] != c)
			temp[j++] = input[i++];
		temp[j++] = input[i++];
	}
	if (input[i] && ft_isspace(input[i]))
		temp[j++] = ' ';
	while (input[i] && ft_isspace(input[i]))
		i++;
	temp[j] = '\0';
	if (input[i] == '\0')
		return (true);
	return (false);
}

static char *trim_hub(char *input)
{
	char	*temp;
	
	temp = ft_calloc(ft_strlen(input) + 1, sizeof(char));
	if(!temp)
		return (NULL);
	while (space_trim(input, temp) == false)
		(void)0;
	return (temp);
}

static int quote_check(const char *input)
{
	char c;
	
	c = 0;
	while (*input != '\0')
	{
		if (*input == '"' || *input == '\'')
		{
			if (c == 0)
				c = *input;
			else if (c == *input)
				c = 0;
		}
		input++;
	}
	return ((c == '\'') + ((c == '\"') * 2));
}

static int input_cleaner(char *input)
{
	char *trim;

	if (!input)
		return (-1);
	trim = trim_hub(input);
	if (!trim)
	{
		printf("Error: failed to allocate memory\n");
		exit(1);
	}
	ft_strlcpy(input, trim, ft_strlen(trim) + 1);
	free(trim);
	return (0);
}

int	input_manager(char **input)
{
	if (quote_check(*input))
	{
		printf("Error: unmatched quote\n");
		return (1);
	}
	input_cleaner(*input);
	return (0);
}
