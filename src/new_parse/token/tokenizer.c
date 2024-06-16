/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncampbel <ncampbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 13:15:24 by ncampbel          #+#    #+#             */
/*   Updated: 2024/06/15 14:32:07 by ncampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../libs/headers.h"

static void	analyze_array(char **array, t_minishell *shell)
{
	check_pipe(array, shell); // check for pipes
	check_left_trunc(array, shell); // check for left redirection
	check_left_apend(array, shell); // check for left double redirection
	check_right_trunc(array, shell); // check for right redirection
	check_right_apend(array, shell); // check for right double redirection
}

// static char *check_meta(char *str)
// {
// 	int		i;
// 	bool	before_quote;

// 	i = -1;
// 	before_quote = true;
// 	while (str[++i] != '\0')
// 	{
// 		if (before_quote == true && (str[i] == N_DQUOTE || str[i] == N_SQUOTE))
// 			before_quote = false;
// 		if (before_quote == true && (str[i] == N_EQUAL))
// 			return (ft_strdup("="));
// 	}
// 	return (NULL);
// }

static int skip_quotes(char *input, int *i) // add to quotes file (?)
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
		if (input[i] == ' ' || input[i] == '=' || input[i] == '$'
			|| input[i] == '|' || input[i] == '<' || input[i] == '>')
			input[i] *= -1;
	}
}

void	tokenizer(t_minishell *shell)
{
	char **array;
	
	mark_tokens(shell->input); // mark special char, spaces and quotes to analyze later
	array = ft_split(shell->input, N_SPACE); // split tokens by n_space
	if (!array)
	{
		// free everything
		exit(1);
	}
	analyze_array(array, shell); // analyze array to create tokens
	token_creation(array, shell); // create tokens
	analyze_tokens(shell->tokens, shell); // analyze tokens to create commands
	free_array(array);
}
