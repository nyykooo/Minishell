/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyze_argument.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncampbel <ncampbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 17:20:31 by ncampbel          #+#    #+#             */
/*   Updated: 2024/06/10 20:09:16 by ncampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../libs/headers.h"

// para remover as quotes podemos verificar se há duas Nquotes seguidas e fazer um split das strings

static void check_quotes_dol(t_arg *input)
{
	int i;

	i = -1;
	if (input->arg == NULL)
		return ;
	while (input->arg[++i])
	{
		if (input->arg[i] == N_DQUOTE)
			input->dq = true;
		else if (input->arg[i] == N_SQUOTE)
			input->sq = true;
		else if (input->arg[i] == N_DOLLAR)
			input->dol = true;
	}
	
}

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

static char *quote_del(t_arg *input)
{
	int	i;
	int size;
	char *new;
	int quotes;
	
	if (input->arg == NULL)
		return NULL;
	size = ft_strlen(input->arg);
	quotes = count_quotes(input->arg);
	new = (char *)malloc((sizeof(char) * size) - quotes + 1);
	if (!new)
		return NULL;
	i = -1;
	quotes = 0;
	while (input->arg[++i])
	{
		new[i - quotes] = input->arg[i];
		if (input->arg[i] == N_DQUOTE || input->arg[i] == N_SQUOTE)
			quotes++;
	}
	new[i - quotes] = '\0';
	if (input->arg)
		free(input->arg);
	return (new);
}

void	analyze_argument(t_token **tokens, t_minishell *shell)
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
				check_quotes_dol(tokens[i]->argument[j]);
				tokens[i]->argument[j]->arg = quote_del(tokens[i]->argument[j]);
				expand_dolar(tokens[i]->argument[j], shell);
			}
		}
	}
}
