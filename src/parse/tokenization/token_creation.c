/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_creation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncampbel <ncampbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 17:08:53 by ncampbel          #+#    #+#             */
/*   Updated: 2024/06/09 10:04:58 by ncampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../libs/headers.h"

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

static t_arg **init_arguments(t_arg **arguments, char **tokens_arg)
{
	int size;
	int j;

	size = ft_array_len(tokens_arg) - count_cmd(tokens_arg) + 2;
	arguments = (t_arg **)malloc(sizeof(t_arg *) * size);
	if (!arguments)
		return (NULL); // error handling
	j = 0;
	while (j < size)
	{
		arguments[j] = (t_arg *)malloc(sizeof(t_arg));
		arguments[j]->arg = NULL;
		if (!arguments[j++])
			return (NULL); // error handling
	}
	arguments[j] = NULL;
	return (arguments);
}

static t_arg **get_arguments(char **tokens_arg, int *i)
{
	int j;
	t_arg **arguments;

	arguments = NULL;
	arguments = init_arguments(arguments, tokens_arg);
	j = 0;
	arguments[j++]->arg = ft_strdup(tokens_arg[(*i)]);
	while (tokens_arg[++(*i)])
	{
		if (check_cmd(tokens_arg[(*i)]) == true)
			break ;
		arguments[j]->arg = ft_strdup(tokens_arg[(*i)]);
		j++;
	}
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
		else if (array[i] != NULL) // criar funcao para criar os arguments
		{
			(*tokens)[j]->cmd = check_meta(array[i]); // check metachars
			(*tokens)[j]->argument = (t_arg **)malloc(sizeof(t_arg *) * 2);
			(*tokens)[j]->argument[0]->arg = ft_strdup(array[i]);
			(*tokens)[j]->argument[1] = NULL;
		}
	}
}

void	create_tokens(char **array, t_token ***tokens)
{
	int i;
	int size;

	i = -1;
	size = count_cmd(array);
	*tokens = (t_token **)malloc(sizeof(t_token *) * size + 1);
	if (!(*tokens))
		return ; // error handling
	while (++i < size)
	{
		(*tokens)[i] = (t_token *)malloc(sizeof(t_token));
		if (!(*tokens)[i])
			free_tokens(*tokens);
	}
	(*tokens)[i] = NULL;
	init_tokens(tokens, array);
}
