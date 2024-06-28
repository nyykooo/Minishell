/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncampbel <ncampbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 13:15:24 by ncampbel          #+#    #+#             */
/*   Updated: 2024/06/28 11:32:44 by ncampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../libs/headers.h"

// static void print_array(char **array)
// {
// 	int i;

// 	i = -1;
// 	while (array[++i])
// 	{
// 		printf("array[%d]: %s\n", i, array[i]);
// 	}
// }

// static void	analyze_array(char ***array, t_minishell *shell)
// {
// 	*array = check_pipe(*array, shell); // check for pipes
// 	// print_array(*array);
// 	*array = check_left_trunc(*array, shell); // check for left redirection
// 	*array = check_left_apend(*array, shell); // check for left double redirection
// 	*array = check_right_trunc(*array, shell); // check for right redirection
// 	*array = check_right_apend(*array, shell); // check for right double redirection
// }

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

// static int skip_quotes(char *input, int *i) // add to quotes file (?)
// {
// 	char quote;

// 	quote = input[(*i)];
// 	input[(*i)] *= -1;
// 	while (input[++(*i)])
// 	{
// 		if (input[(*i)] == quote)
// 		{
// 			input[(*i)] *= -1;
// 			return ((*i));
// 		}
// 	}
// 	return ((*i));
// }

static void	mark_tokens(char *input)
{
	int i;

	i = -1;
	while (input[++i])
	{
		if (input[i] == '\'' || input[i] == '\"')
			i = skip_quotes(input, &i);
		if (input[i] == ' ' || input[i] == '=' || input[i] == '$')
			input[i] *= -1;
	}
}

static void clear_commands(t_cmd *command, t_minishell *shell)
{
	t_cmd *tmp;

	tmp = command;
	while (tmp)
	{
		tmp->cmd = quote_del(tmp->cmd, shell);
		tmp = tmp->next;
	}
}

static void reset_shell(t_minishell *shell)
{
	while (shell->commands)
	{
		while (shell->commands->arguments)
		{
			if (shell->commands->arguments->prev)
				shell->commands->arguments = shell->commands->arguments->prev;
			else
				break;
		}
		if (shell->commands->prev)
			shell->commands = shell->commands->prev;
		else
			break;
	}
}

static void mark_redir(t_cmd *command)
{
	t_cmd *temp;
	
	temp = command->prev;
	if (temp)
	{
		if (temp->type == T_LTRUNC)
			command->rtrunc = true;
		else if (temp->type == T_RTRUNC)
			command->rtrunc = true;
		else if (temp->type == T_LAPEND)
			command->rappend = true;
		else if (temp->type == T_RAPEND)
			command->rappend = true;
	}
}

static void	get_command_path(t_minishell *shell)
{
	t_cmd *commands;

	commands = shell->commands;
	while (commands)
	{
		if (commands->cmd)
			if (access(commands->cmd, F_OK) == 0)
			{
				commands->path = ft_strdup(commands->cmd);
				mark_redir(commands);
			}
		commands = commands->next;
	}
}

void	tokenizer(t_minishell *shell)
{
	char **array;
	
	expand_dolar(&shell->input, shell); // expand dolar variables
	expand_tildes(&shell->input, shell); // expand tildes
	expand_pipes_redir(shell); // expand pipes and redirections
	mark_tokens(shell->input); // mark special char, spaces and quotes to analyze later
	array = ft_split(shell->input, N_SPACE); // split tokens by n_space
	if (!array)
	{
		// free everything
		exit(1);
	}
	// analyze_array(&array, shell); // analyze array to create tokens
	token_creation(array, shell); // create tokens
	analyze_tokens(shell->tokens, shell); // analyze tokens to create commands
	reset_shell(shell);
	clear_commands(shell->commands, shell);
	get_command_path(shell); // get paths for commands
	free_array(array);
}
