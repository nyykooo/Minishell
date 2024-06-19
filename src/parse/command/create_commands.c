/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_commands.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncampbel <ncampbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 14:49:42 by ncampbel          #+#    #+#             */
/*   Updated: 2024/06/19 14:54:11 by ncampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../libs/headers.h"

static	void	init_cmd(t_minishell *shell, t_token *tokens)
{
	t_cmd	*cmd;

	cmd = ft_calloc(1, sizeof(t_cmd));
	ft_cmdadd_back(&shell->commands, cmd);
	cmd->cmd = ft_strdup(tokens->content);
	cmd->type = tokens->type;
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
	ft_argadd_back(&shell->commands->arguments, arg);
	arg->arg = ft_strdup(argument);
}

void	create_command(t_token *tokens, t_minishell *shell)
{
	t_token *tmp;

	tmp = tokens;
	init_cmd(shell, tmp);
	if (!shell->commands)
	{
		//free everything
		printf("Error: malloc failed create commands\n");
		exit (1);
	}
	if (check_tokens(tmp) != 2)
		tmp = tmp->next;
	while (tmp && check_tokens(tmp) == 2)
	{
		init_arg(shell, tmp->content);
		tmp = tmp->next;
	}
}
