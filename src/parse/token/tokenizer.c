/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncampbel <ncampbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 13:15:24 by ncampbel          #+#    #+#             */
/*   Updated: 2024/08/07 19:27:22 by ncampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../libs/headers.h"

static void	mark_tokens(char *input)
{
	int	i;

	i = -1;
	while (input[++i])
	{
		if (input[i] == '\'' || input[i] == '\"')
			i = skip_quotes(input, &i);
		if (input[i] == ' ')
			input[i] *= -1;
	}
}

static void	clear_commands(t_cmd *command)
{
	t_cmd	*tmp;

	tmp = command;
	while (tmp)
	{
		tmp->cmd = quote_del(tmp->cmd);
		tmp = tmp->next;
	}
}

static void	reset_shell(t_minishell *shell)
{
	while (shell->commands)
	{
		while (shell->commands->arguments)
		{
			if (shell->commands->arguments->prev)
				shell->commands->arguments = shell->commands->arguments->prev;
			else
				break ;
		}
		if (shell->commands->prev)
			shell->commands = shell->commands->prev;
		else
			break ;
	}
}

static void	mark_redir(t_cmd *command)
{
	t_cmd	*temp;

	temp = command->prev;
	if (temp)
	{
		if (temp->type == T_LTRUNC)
			command->input_file = true;
		else if (temp->type == T_RTRUNC)
			command->rtrunc = true;
		else if (temp->type == T_LAPEND)
			command->lappend = true;
		else if (temp->type == T_RAPEND)
			command->rappend = true;
	}
}

static void	get_cmd_path(t_minishell *shell)
{
	t_cmd	*commands;

	commands = shell->commands;
	while (commands)
	{
		if (commands->cmd)
			mark_redir(commands);
		commands = commands->next;
	}
}

static bool	ft_verify_fn(t_minishell *shell)
{
	t_token	*token;

	token = shell->tokens;
	if (!token)
		return (false);
	if (!token->next && ft_strcmp(token->content, ".") == 0)
	{
		ft_print_error(false, 2, 1, "minishell: .: filename argument required\n");
		return (false);
	}
	return (true);
}

static bool	ft_verify_unexpected_token(t_minishell *shell)
{
	t_token	*token;

	token = shell->tokens;
	while (token)
	{
		if (token->type >= T_RTRUNC && token->type <= T_PIPE)
		{
			if (token->type == T_PIPE && (!token->prev || (token->next && token->next->type == T_PIPE)))
			{
				ft_print_error(false, 2, 1, "minishell: syntax error near unexpected token `|'\n");
				return (false);
			}
			if (!token->next)
			{
				ft_print_error(false, 2, 1, "minishell: syntax error near unexpected token `newline'\n");
				return (false);
			}
			if (token->type != T_PIPE && token->next->type >= T_RTRUNC)
			{
				ft_print_error(false, 2, 3, "minishell: syntax error near unexpected token `", token->next->content, "'\n");
				return (false);
			}
		}
		token = token->next;
	}
	return (true);
}

void	tokenizer(t_minishell *shell)
{
	char	**array;

	expand_dolar(&shell->input, shell);
	expand_tildes(&shell->input, shell);
	expand_hashtag(&shell->input);
	expand_pipes_redir(shell);
	mark_tokens(shell->input);
	array = ft_split(shell->input, N_SPACE);
	if (!array)
	{
		free_shell(shell);
		exit(1);
	}
	token_creation(array, shell);
	free_array(array);
	if (ft_verify_unexpected_token(shell) && ft_verify_fn(shell))
	{
		analyze_tokens(shell->tokens, shell);
		reset_shell(shell);
		clear_commands(shell->commands);
		get_cmd_path(shell);
	}
}
