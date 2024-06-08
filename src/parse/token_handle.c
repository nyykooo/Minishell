/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_handle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunhenr <brunhenr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 13:15:24 by ncampbel          #+#    #+#             */
/*   Updated: 2024/06/07 14:42:07 by brunhenr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libs/headers.h"

static bool check_cmd(char *tokens_arg)
{
	if (ft_strcmp(tokens_arg, "echo") == 0 || ft_strcmp(tokens_arg, "cd") == 0
		|| ft_strcmp(tokens_arg, "pwd") == 0 || ft_strcmp(tokens_arg, "export") == 0
		|| ft_strcmp(tokens_arg, "unset") == 0 || ft_strcmp(tokens_arg, "env") == 0
		|| ft_strcmp(tokens_arg, "exit") == 0 || ft_strcmp(tokens_arg, "ls") == 0
		|| ft_strcmp(tokens_arg, "grep") == 0 || ft_strcmp(tokens_arg, "cat") == 0
		|| ft_strcmp(tokens_arg, "wc") == 0 || ft_strcmp(tokens_arg, "sort") == 0
		|| ft_strcmp(tokens_arg, "uniq") == 0 || ft_strcmp(tokens_arg, "cut") == 0
		|| ft_strcmp(tokens_arg, "paste") == 0 || ft_strcmp(tokens_arg, "join") == 0
		|| ft_strcmp(tokens_arg, "comm") == 0 || ft_strcmp(tokens_arg, "diff") == 0
		|| ft_strcmp(tokens_arg, "sed") == 0 || ft_strcmp(tokens_arg, "awk") == 0
		|| ft_strcmp(tokens_arg, "tr") == 0)
		return (true);
	else
		return (false);
}

static char *check_meta(char *str)
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

static int count_cmd(char **tokens_arg)
{
	int i;
	int size;

	i = -1;
	size = 0;
	while (tokens_arg[++i])
	{
		if (check_cmd(tokens_arg[i]) == true)
			size++;
	}
	if (size == 0)
		size = 1;
	return (size);
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
		if (input[i] == ' ' || input[i] == '=')
			input[i] *= -1;
	}
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
	return (new);
}

static char **get_arguments(char **tokens_arg, int *i)
{
	int	size;
	int j;
	char **arguments;
	char *temp;

	size = ft_array_len(tokens_arg) - count_cmd(tokens_arg) + 2;
	arguments = (char **)malloc(sizeof(char *) * size);
	if (!arguments)
		return (NULL); // error handling
	j = 0;
	arguments[j++] = ft_strdup(tokens_arg[(*i)]);
	while (tokens_arg[++(*i)])
	{
		if (check_cmd(tokens_arg[(*i)]) == true)
			break ;
		temp = ft_strdup(tokens_arg[(*i)]);
		arguments[j] = quote_del(temp); //delete quotes??
		free(temp);
		j++;
	}
	arguments[j] = NULL;
	return (arguments);
}

static void init_tokens(t_token ***tokens, char **array)
{
	int i;
	int j;
	int len;

	i = -1;
	j = 0;
	len = ft_array_len(array);
	while (++i < len)
	{
		if (array[i] != NULL && check_cmd(array[i]) == true)
		{
			(*tokens)[j]->cmd = ft_strdup(array[i]);
			(*tokens)[j]->argument = get_arguments(array, &i);
			j++;
		}
		else if (array[i] != NULL)
		{
			(*tokens)[j]->cmd = check_meta(array[i]); // check metachars
			(*tokens)[j]->argument = (char **)malloc(sizeof(char *) * 2);
			(*tokens)[j]->argument[0] = ft_strdup(array[i]);
			(*tokens)[j]->argument[1] = NULL;
		}
	}
}

static void	create_tokens(char **array, t_token ***tokens)
{	
	int	i;
	int	size;

	i = -1;
	size = count_cmd(array);
	*tokens = (t_token **)malloc(sizeof(t_token *) * (size + 1));
	if (!(*tokens))
		return ; // error handling
	while (++i < size)
	{
		(*tokens)[i] = (t_token *)malloc(sizeof(t_token));
		if (!(*tokens)[i])
		{
			(*tokens)[i] = NULL;
			free_tokens(*tokens);
			free(*tokens);
			return ;
		}
	}
	(*tokens)[i] = NULL;
	init_tokens(tokens, array);
}

t_token **token_manager(char *input)
{
	char **array;
	t_token **tokens;

	tokens = NULL;
	mark_tokens(input);
	array = ft_split(input, N_SPACE);
	if (!array)
		return (NULL);
	create_tokens(array, &tokens);
	free_array(array);
	return (tokens);
}
