/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_commands.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncampbel <ncampbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 14:49:42 by ncampbel          #+#    #+#             */
/*   Updated: 2024/06/16 11:57:20 by ncampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../libs/headers.h"

static	void	init_cmd(t_minishell *shell, t_token *tokens)
{
	t_cmd	*cmd;

	cmd = ft_calloc(1, sizeof(t_cmd));
	if (shell->commands)
	{
		shell->commands->next = cmd;
		cmd->prev = shell->commands;
	}
	else
		shell->commands = cmd;
	cmd->cmd = ft_strdup(tokens->content);
	if (tokens->type == T_PIPE)
		cmd->pipe = true;
	else if (tokens->type == T_RAPEND)
		cmd->rappend = true;
	else if (tokens->type == T_LAPEND)
		cmd->lappend = true;
	else if (tokens->type == T_RTRUNC)
		cmd->rtrunc = true;
	else if (tokens->type == T_LTRUNC)
		cmd->ltrunc = true;
}

static	void	init_arg(t_minishell *shell, char *argument)
{
	t_arg *arg;

	arg = ft_calloc(1, sizeof(t_arg));
	if (shell->commands->arguments)
	{
		shell->commands->arguments->next = arg;
		arg->prev = shell->commands->arguments;
	}
	else
		shell->commands->arguments = arg;
}

void	create_command(t_token *tokens, t_minishell *shell, int *i)
{
	t_token *tmp;

	tmp = tokens;
	init_cmd(shell, tokens);
	if (!shell->commands->arguments)
	{
		//free everything
		exit (1);
	}
	tokens = tokens->next;
	while (tokens && check_cmd(tokens->content) == 2)
	{
		init_arg(shell, tokens->content);
		tokens = tokens->next;
	}
	analyze_arguments(shell, tmp);
}
