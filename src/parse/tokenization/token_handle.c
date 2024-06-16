/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_handle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncampbel <ncampbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 13:15:24 by ncampbel          #+#    #+#             */
/*   Updated: 2024/06/13 14:17:33 by ncampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../libs/headers.h"

char *check_meta(char *str)
{
	int		i;
	bool	before_quote;

	i = -1;
	before_quote = true;
	while (str[++i] != '\0')
	{
		if (before_quote == true && (str[i] == N_DQUOTE || str[i] == N_SQUOTE))
			before_quote = false;
		if (before_quote == true && (str[i] == N_EQUAL))
			return (ft_strdup("="));
	}
	return (NULL);
}

static int skip_quotes(char *input, int *i)
{
	char quote;

	quote = input[(*i)];
	input[(*i)] *= -1;
	while (input[++(*i)])
	{
		if (input[(*i)] == quote)
		{
			input[(*i)] *= -1;
			return ((*i));
		}
	}
	return ((*i));
}

static void	mark_tokens(char *input)
{
	int i;

	i = -1;
	while (input[++i])
	{
		if (input[i] == '\'' || input[i] == '\"')
			i = skip_quotes(input, &i);
		if (input[i] == ' ' || input[i] == '=' || input[i] == '$')
			input[i] *= -1;
	}
}

t_token **token_manager(char *input)
{
	char **array;
	t_token **tokens;

	mark_tokens(input);
	array = ft_split(input, N_SPACE);
	if (!array)
		return (NULL);
	create_tokens(array, &tokens);
	free_array(array);
	return (tokens);
}
