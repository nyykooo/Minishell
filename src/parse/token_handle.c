/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_handle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncampbel <ncampbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 13:15:24 by ncampbel          #+#    #+#             */
/*   Updated: 2024/05/23 18:04:28 by ncampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libs/headers.h"

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
		if (input[i] == ' ')
			input[i] *= -1;
	}
}

static void	quote_del(char **input)
{
	int	i;
	int size;
	char *new;
	
	size = ft_strlen(*input);
	new = (char *)malloc((sizeof(char) * size)  - 1);
	if (!new)
		return ;
	i = 0;
	while ((*input)[++i])
		new[i - 1] = (*input)[i];
	new[i - 2] = '\0';
	free(*input);
	*input = new;
}

// static void	create_tokens(char **tokens_arg, t_token ***tokens, int size)
// {
// 	int i;

// 	i = -1;
// 	*tokens = (t_token **)malloc(sizeof(t_token *) * size);
// 	while (tokens_arg[++i])
// 	{
// 		(*tokens)[i]->argument = tokens_arg[i];
// 		(*tokens)[i]->cmd = 0;
// 	}
// }

char	**token_manager(char *input)
{
	int	i;
	char **tokens_arg;
	// t_token **tokens;

	i = -1;
	mark_tokens(input);
	tokens_arg = ft_split(input, N_SPACE);
	if (!tokens_arg)
		return (NULL);
	while (tokens_arg[++i])
	{
		if (tokens_arg[i][0] == N_DQUOTE || tokens_arg[i][0] == N_SQUOTE)
			quote_del(&tokens_arg[i]);
	}
	// create_tokens(tokens_arg, &tokens, i);
	return (tokens_arg);
}
