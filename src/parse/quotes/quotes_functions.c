/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunhenr <brunhenr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 14:40:02 by ncampbel          #+#    #+#             */
/*   Updated: 2024/06/22 19:18:02 by brunhenr         ###   ########.fr       */
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

char *quote_del(char *input, t_minishell *shell)
{
	int	i;
	int size;
	char *new;
	int quotes;
	
	size = ft_strlen(input);
	quotes = count_quotes(input);
	new = (char *)malloc((sizeof(char) * size) - quotes + 1);
	if (!new)
	{
		//free everything
		printf("Error: failed to allocate memory %s\n", shell->input);
		exit (1);
	}
	i = -1;
	quotes = 0;
	while (input[++i])
	{
		new[i - quotes] = input[i];
		if (input[i] == N_DQUOTE || input[i] == N_SQUOTE)
			quotes++;
	}
	new[i - quotes] = '\0';
	if (input)
		free(input);
	return (new);
}

// expand_quotes is a function that expands the quotes in the arguments
// think if it makes more sense to expand the quotes in the tokenizer

void expand_quotes(t_token *token, t_minishell *shell)
{
	int		i;
	bool	flag;
	t_token *curr;

	i = -1;
	flag = false;
	curr = token;
	if (token->content == NULL)
		return ;
	while (token->content[++i] != '\0')
	{
		if ((token->content[i] == N_DQUOTE || token->content[i] == N_SQUOTE)
			&& ((token->content[i + 1] == '\0') || (i != 0)))
			break ;
		else if (token->content[i] == N_DQUOTE || token->content[i] == N_SQUOTE)
			flag = true;
	}
	if (token->content[i + 1] == 0 || token->content[i] == 0)
		return ;
	if (flag)
		i++;
	include_token(shell, token->content + i, curr);
	token->content[i] = '\0';
	expand_quotes(token->next, shell);
}

int	skip_quotes(char *input, int *i)
{
	char	quote;

	quote = input[(*i)];
	input[(*i)] *= -1;
	while (input[++(*i)])
	{
		if (input[(*i)] == quote)
		{
			input[(*i)] *= -1;
			return ((*i));
		}
		if (input[(*i)] == '=' || (input[(*i)] == '$' && quote == '"'))
			input[(*i)] *= -1;
	}
	return ((*i));
}

int	skip_nquotes(char *input, int *i)
{
	char	quote;

	quote = input[(*i)];
	while (input[++(*i)])
	{
		if (input[(*i)] == quote)
			return ((*i));
	}
	return ((*i));
}