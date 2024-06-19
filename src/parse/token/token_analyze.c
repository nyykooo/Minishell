/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_analyze.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncampbel <ncampbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 17:08:53 by ncampbel          #+#    #+#             */
/*   Updated: 2024/06/19 15:05:55 by ncampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../libs/headers.h"

// check_token is a function that checks the type of a token

int check_tokens(t_token *tokens)
{
	if (tokens->type == T_EMPTY)
		return (0);
	else if (tokens->type == T_COMMAND)
		return (1);
	else if (tokens->type == T_ARG)
		return (2);
	else if (tokens->type == T_RTRUNC)
		return (3);
	else if (tokens->type == T_RAPEND)
		return (4);
	else if (tokens->type == T_LTRUNC)
		return (5);
	else if (tokens->type == T_LAPEND)
		return (6);
	else if (tokens->type == T_PIPE)
		return (7);
	else if (tokens->type == T_EXEC)
		return (8);
	else
		return (0);
}

// static bool check_cmd(char *tokens_arg)
// {
// 	if (ft_strcmp(tokens_arg, "echo") == 0 || ft_strcmp(tokens_arg, "cd") == 0
// 		|| ft_strcmp(tokens_arg, "pwd") == 0 || ft_strcmp(tokens_arg, "export") == 0
// 		|| ft_strcmp(tokens_arg, "unset") == 0 || ft_strcmp(tokens_arg, "env") == 0
// 		|| ft_strcmp(tokens_arg, "exit") == 0)
// 		return (true);
// 	else
// 		return (false);
// }

// check_meta is a function that checks if a token has a meta character (IS IT REALLY NECESSARY????)

// static char	*check_meta(char *str)
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

// count_cmd is a function that counts the number of commands in the input

// static int count_cmd(char **tokens_arg)
// {
// 	int i;
// 	int size;

// 	i = -1;
// 	size = 0;
// 	while (tokens_arg[++i])
// 	{
// 		if (check_cmd(tokens_arg[i]) == true)
// 			size++;
// 	}
// 	if (size == 0)
// 		size = 1;
// 	return (size);
// }

// analyze_tokens is a function that analyzes the tokens and creates the commands

static void analyze_commands(t_minishell *shell)
{
	t_cmd *temp;
	
	temp = shell->commands;
	while (temp)
	{
		analyze_arguments(shell, temp);
		temp = temp->next;
	}
}

void	analyze_tokens(t_token *tokens, t_minishell *shell)
{
	while (tokens != NULL)
	{
		if (check_tokens(tokens) == 1) // checks if token is a command, a pipe or a executable
		{
			shell->n_cmd++;
			create_command(tokens, shell); // create_command is a function that creates a command structure
		}
		else if (check_tokens(tokens) == 7)
		{
			shell->n_pipe++;
			create_command(tokens, shell);
		}
		else if (check_tokens(tokens) == 8)
			create_command(tokens, shell);
		tokens = tokens->next;
	}
	analyze_commands(shell); // analyze_commands is a function that analyzes the command's arguments
	return ;
}
