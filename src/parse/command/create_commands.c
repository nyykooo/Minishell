/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_commands.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncampbel <ncampbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 14:49:42 by ncampbel          #+#    #+#             */
/*   Updated: 2024/08/07 20:15:02 by ncampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../libs/headers.h"

static	void	init_arg(t_cmd *command, char *argument)
{
	t_arg	*arg;

	arg = ft_calloc(1, sizeof(t_arg));
	ft_argadd_back(&command->arguments, arg);
	arg->arg = ft_strdup(argument);
}

static	void	init_cmd(t_minishell *shell, t_token *tokens)
{
	t_cmd	*cmd;

	cmd = ft_calloc(1, sizeof(t_cmd));
	ft_cmdadd_back(&shell->commands, cmd);
	cmd->cmd = ft_strdup(tokens->content);
	cmd->type = tokens->type;
	cmd->shell = shell;
	cmd->here_doc_fd = -1;
	tokens = tokens->next;
	while (tokens && (tokens->type == T_ARG || tokens->type == T_EMPTY))
	{
		if (tokens->prev->prev && tokens->prev->prev->type == T_LAPEND)
			break ;
		init_arg(cmd, tokens->content);
		tokens = tokens->next;
	}
}

static void	ft_mark_redir(t_cmd *command)
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

void	ft_mark_commands(t_minishell *shell)
{
	t_cmd	*commands;

	commands = shell->commands;
	while (commands)
	{
		if (commands->cmd)
			ft_mark_redir(commands);
		commands = commands->next;
	}
}

void	create_command(t_token *tokens, t_minishell *shell)
{
	t_token	*tmp;

	tmp = tokens;
	init_cmd(shell, tmp);
	if (!shell->commands)
		ft_print_error(true, 0, 1, "Error: malloc failed create commands\n");
}
