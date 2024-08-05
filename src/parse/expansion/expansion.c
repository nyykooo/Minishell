/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncampbel <ncampbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 17:06:10 by ncampbel          #+#    #+#             */
/*   Updated: 2024/08/05 15:55:47 by ncampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// contar quantos pipes e redirects precisam de espaços extras (1 ou 2)
// alocar memoria baseado no length da string + add_space
// copiar a string original para a nova string com os espaços extras

#include "../../../libs/headers.h"

static bool	is_pipe_redir(char pr)
{
	if (pr && (pr == '>' || pr == '<' || pr == '|'))
		return (true);
	return (false);
}

static int	what_redir(char *str)
{
	if (str[0] != str[1])
	{
		if (*str == '<')
			return (T_LTRUNC);
		else if (*str == '>')
			return (T_RTRUNC);
		else if (*str == '|')
			return (T_PIPE);
	}
	else
	{
		if (*str == '<')
			return (T_LAPEND);
		else if (*str == '>')
			return (T_RAPEND);
	}
	return (0);
}


static void	count_space_pr_differ(char *input, int *i, int *add_space)
{
	if (what_redir(&(input[*i])) == T_RAPEND
		|| what_redir(&(input[*i])) == T_LAPEND)
	{
		if (!input[*i] || !input[(*i) + 2])
			return ;
		if (input[(*i) + 2] != ' ')
			(*add_space)++;
		if (*i != 0 && input[(*i) - 1] != ' ')
			(*add_space)++;
		(*i)++;
	}
	else
	{
		if (!input[*i] || !input[(*i) + 1])
			return ;
		if (input[(*i) + 1] != ' ')
			(*add_space)++;
		if (*i != 0 && input[(*i) - 1] != ' ')
			(*add_space)++;
	}
	(*i)++;
}

static int	count_spaces(char *str)
{
	int	i;
	int	add_space;

	i = 0;
	add_space = 0;
	while (str[i])
	{
		if (is_pipe_redir(str[i]) && !ft_is_inside_quotes(str, i))
			count_space_pr_differ(str, &i, &add_space);
		i++;
	}
	return (add_space);
}

static void	insert_spaces(char *input, char *new)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (input[i])
	{
		while (input[i] && ((!is_pipe_redir(input[i])
			|| ft_is_inside_quotes(input, i))))
			new[j++] = input[i++];
		if (!input[i])
			break ;
		if (j != 0 && new[j - 1] != ' ')
			new[j++] = ' ';
		if (what_redir(&input[i]) == T_RAPEND
			|| what_redir(&input[i]) == T_LAPEND)
			new[j++] = input[i++];
		new[j++] = input[i++];
		if (input[i] != ' ')
			new[j++] = ' ';
	}
	new[j] = '\0';
}

void	expand_pipes_redir(t_minishell *shell)
{
	int	add_space;
	int	len;
	char *new_str;

	add_space = count_spaces(shell->input);
	if (add_space == 0)
		return ;
	len = ft_strlen(shell->input) + add_space + 1;
	new_str = malloc(len);
	if (!new_str)
	{
		printf("error: malloc failed\n");
		exit (1);
	}
	insert_spaces(shell->input, new_str);
	free(shell->input);
	shell->input = new_str;
}
