/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pipe_redir2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunhenr <brunhenr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 09:38:55 by brunhenr          #+#    #+#             */
/*   Updated: 2024/08/14 10:16:03 by brunhenr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libs/headers.h"

void	ft_add_argument(t_arg **main_cmd_args, t_arg *new_node)
{
	t_arg	*temp;

	temp = *main_cmd_args;
	if (!temp)
		*main_cmd_args = new_node;
	else
	{
		while (temp->next)
			temp = temp->next;
		temp->next = new_node;
	}
}

static void	ft_copy_arguments(t_arg *src, t_arg **dest)
{
	t_arg	*current_arg;
	t_arg	*new_arg_list;
	t_arg	**new_arg_list_tail;
	t_arg	*new_arg;

	current_arg = src;
	new_arg_list = NULL;
	new_arg_list_tail = &new_arg_list;
	while (current_arg)
	{
		new_arg = calloc(1, sizeof(t_arg));
		if (current_arg->arg)
			new_arg->arg = ft_strdup(current_arg->arg);
		*new_arg_list_tail = new_arg;
		new_arg_list_tail = &new_arg->next;
		current_arg = current_arg->next;
	}
	*dest = new_arg_list;
}

static void	ft_corner_case(t_cmd *cmd)
{
	t_cmd	*new_cmd;
	t_arg	*current_arg;

	current_arg = NULL;
	new_cmd = calloc(1, sizeof(t_cmd));
	new_cmd->type = T_COMMAND;
	new_cmd->shell = ft_get_shell();
	if (cmd->next && cmd->next->arguments && cmd->next->arguments->arg)
		new_cmd->cmd = ft_strdup(cmd->next->arguments->arg);
	if (cmd->next && cmd->next->arguments && cmd->next->arguments->next)
		current_arg = cmd->next->arguments->next;
	ft_copy_arguments(current_arg, &new_cmd->arguments);
	if (cmd->next)
	{
		new_cmd->next = cmd->next->next;
		cmd->next->next = new_cmd;
		new_cmd->prev = cmd->next;
	}
	else
	{
		new_cmd->next = NULL;
		new_cmd->prev = cmd;
	}
}

bool	is_not_pipe_or_redir_arg(t_cmd **cmd)
{
	if ((*cmd)->next && (*cmd)->next->arguments && \
	strcmp((*cmd)->next->arguments->arg, "|") != 0 && \
	strcmp((*cmd)->next->arguments->arg, ">") != 0 && \
	strcmp((*cmd)->next->arguments->arg, ">>") != 0 && \
	strcmp((*cmd)->next->arguments->arg, "<") != 0)
	{
		ft_corner_case(*cmd);
		*cmd = (*cmd)->next->next;
		return (true);
	}
	return (false);
}
