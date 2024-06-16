/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncampbel <ncampbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 14:40:02 by ncampbel          #+#    #+#             */
/*   Updated: 2024/06/16 20:34:38 by ncampbel         ###   ########.fr       */
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

char *quote_del(t_arg *input, t_minishell *shell)
{
	int	i;
	int size;
	char *new;
	int quotes;
	
	size = ft_strlen(input->arg);
	quotes = count_quotes(input->arg);
	new = (char *)malloc((sizeof(char) * size) - quotes + 1);
	if (!new)
	{
		//free everything
		printf("Error: failed to allocate memory %s\n", shell->input);
		exit (1);
	}
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

// expand_quotes is a function that expands the quotes in the arguments

void expand_quotes(t_arg *argument, t_minishell *shell)
{
	int		i;
	bool	flag;

	i = -1;
	flag = false;
	if (argument->arg == NULL)
		return ;
	while (argument->arg[++i] != '\0')
	{
		if ((argument->arg[i] == N_DQUOTE || argument->arg[i] == N_SQUOTE)
			&& ((argument->arg[i + 1] == '\0') || (i != 0)))
			break ;
		else if (argument->arg[i] == N_DQUOTE || argument->arg[i] == N_SQUOTE)
			flag = true;
	}
	if (argument->arg[i] == 0)
		return ;
	if (flag)
		i++;
	include_arg(shell, argument->arg + i);
	argument->arg[i] = '\0';
	expand_quotes(argument->next, shell);
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
	}
	return ((*i));
}