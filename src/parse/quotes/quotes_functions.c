/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncampbel <ncampbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 14:40:02 by ncampbel          #+#    #+#             */
/*   Updated: 2024/08/13 19:54:38 by ncampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../libs/headers.h"

static int	count_quotes(char *input)
{
	int	i;
	int	quotes;

	i = -1;
	quotes = 0;
	while (input[++i])
	{
		if (input[i] == N_DQUOTE || input[i] == N_SQUOTE)
			quotes++;
	}
	return (quotes);
}

char	*ft_quote_del(char *input)
{
	int		i;
	int		size;
	char	*new;
	int		quotes;

	size = ft_strlen(input);
	quotes = count_quotes(input);
	new = (char *)malloc((sizeof(char) * size) - quotes + 1);
	if (!new)
		ft_print_error(true, 1, 1, "Error: failed to allocate memory\n");
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

void	ft_expand_quotes(t_token *token, t_minishell *shell)
{
	int		i;
	bool	flag;
	t_token	*curr;

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
	ft_include_token(shell, token->content + i, curr);
	token->content[i] = '\0';
	ft_expand_quotes(token->next, shell);
}

int	ft_skip_quotes(char *input, int *i)
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
	}
	return ((*i));
}

int	ft_is_inside_quotes(char *str, size_t index)
{
	char	c;

	c = 0;
	if (!str || index > ft_strlen(str))
		return (0);
	while (*str && index--)
	{
		if (!c)
		{
			if (*str == '\'' || *str == '\"')
				c = *str;
		}
		else if (c == *str)
			c = 0;
		str++;
	}
	if (c == *str)
		c = 0;
	return ((c == '\'') + ((c == '\"') * 2));
}
