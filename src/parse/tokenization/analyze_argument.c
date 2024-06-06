/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyze_argument.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncampbel <ncampbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 17:20:31 by ncampbel          #+#    #+#             */
/*   Updated: 2024/06/06 17:38:24 by ncampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../libs/headers.h"

static int count_quotes(char *input)
{
	int i;
	int quotes;

	i = -1;
	quotes = 0;
	while (input[++i])
	{
		if (input[i] == N_DQUOTE || input[i] == N_SQUOTE)
			quotes++;
	}
	return (quotes);
}

static char *quote_del(char *input)
{
	int	i;
	int size;
	char *new;
	int quotes;
	
	size = ft_strlen(input);
	quotes = count_quotes(input);
	new = (char *)malloc((sizeof(char) * size) - quotes + 1);
	if (!new)
		return NULL;
	i = -1;
	quotes = 0;
	while (input[++i])
	{
		new[i - quotes] = input[i];
		if (input[i] == N_DQUOTE || input[i] == N_SQUOTE)
			quotes++;
	}
	new[i - quotes] = '\0';
	free(input);
	return (new);
}

void	analyze_argument(t_token **tokens)
{
	int	i;
	int	j;

	i = -1;
	while (tokens[++i] != NULL)
	{
		if (tokens[i]->argument != NULL)
		{
			j = -1;
			while (tokens[i]->argument[++j] != NULL)
			{
				tokens[i]->argument[j] = quote_del(tokens[i]->argument[j]); // mark which quote were removed
				// look for $
			}
		}
	}
}
