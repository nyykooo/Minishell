/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pipe_redir.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunhenr <brunhenr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 16:59:15 by brunhenr          #+#    #+#             */
/*   Updated: 2024/08/12 21:40:13 by brunhenr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libs/headers.h"

void	ft_corner_case(t_cmd *cmd)
{
	t_cmd	*new_cmd;
	t_arg	*current_arg;
	t_arg	*new_arg_list;
	t_arg	*new_arg;
	t_arg	**new_arg_list_tail;

	new_cmd = malloc(sizeof(t_cmd));
	new_cmd->type = T_COMMAND;
	new_cmd->rtrunc = false;
	new_cmd->rappend = false;
	new_cmd->input_file = false;
	if (cmd->next && cmd->next->arguments && cmd->next->arguments->arg)
		new_cmd->cmd = ft_strdup(cmd->next->arguments->arg);
	if (cmd->next && cmd->next->arguments && cmd->next->arguments->next)
		current_arg = cmd->next->arguments->next;
	new_arg_list = NULL;
	new_arg_list_tail = &new_arg_list;
	while (current_arg)
	{
		new_arg = calloc(1, sizeof(t_arg));
		new_arg->arg = ft_strdup(current_arg->arg);
		*new_arg_list_tail = new_arg;
		new_arg_list_tail = &new_arg->next;
		current_arg = current_arg->next;
	}
	new_cmd->arguments = new_arg_list;
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

bool	ft_is_pipe_or_redir(t_cmd **cmd, int i)
{
	//t_cmd	*temp;

	if (i == 0 && ((*cmd)->type == T_RTRUNC || (*cmd)->type == T_RAPEND || \
	(*cmd)->type == T_LTRUNC))
	{
		if ((*cmd)->next && (*cmd)->next->arguments && strcmp((*cmd)->next->arguments->arg, "|") != 0 && \
		strcmp((*cmd)->next->arguments->arg, ">") != 0 && \
		strcmp((*cmd)->next->arguments->arg, ">>") != 0 && \
		strcmp((*cmd)->next->arguments->arg, "<") != 0)
		{
			ft_corner_case(*cmd);
			*cmd = (*cmd)->next->next;
			//printf("LOGO APOS O CORNER cmd->cmd: %s\n", (*cmd)->cmd);
		}
		// temp = *cmd;
		// while (temp)
		// {
		// 	printf("temp->cmd: %s\n", temp->cmd);
		// 	printf("temp->type: %d\n", temp->type);
		// 	if (temp->arguments)
		// 		printf("temp->arguments->arg: %s\n", temp->arguments->arg);
		// 	temp = temp->next;
		// }
		return (false);
	}
	else if ((*cmd)->prev && (*cmd)->prev->type == T_PIPE && \
	((*cmd)->type == T_RTRUNC || (*cmd)->type == T_RAPEND || \
	(*cmd)->type == T_LTRUNC))
	{
		//ft_corner_case(*cmd);
		//*cmd = (*cmd)->next->next;
		return (false);
	}
	else if ((*cmd)->type == T_RAPEND || (*cmd)->type == T_RTRUNC || \
	(*cmd)->type == T_LTRUNC || (*cmd)->type == T_LAPEND || \
	(*cmd)->type == T_PIPE)
		return (true);
	return (false);
}

bool	ft_is_file(t_cmd *cmd)
{
	if (cmd->prev != NULL && (cmd->prev->type == T_RAPEND || \
	cmd->prev->type == T_RTRUNC || \
	cmd->prev->type == T_LTRUNC || \
	cmd->prev->type == T_LAPEND))
		return (true);
	// else if (cmd->type == T_RAPEND || cmd->type == T_RTRUNC || 
	// cmd->type == T_LTRUNC)
	// 	return (true);
	return (false);
}

bool	ft_has_pipe(t_cmd *cmd_temp)
{
	int		has_pipe;
	t_cmd	*temp;

	has_pipe = 0;
	temp = cmd_temp;
	while (temp != NULL)
	{
		if (temp->type == T_PIPE)
		{
			has_pipe = 1;
			break ;
		}
		temp = temp->next;
	}
	return (has_pipe);
}

void	ft_nopipe(int in_fd, int out_fd)
{
	if (in_fd >= 0)
	{
		dup2(in_fd, STDIN_FILENO);
		close(in_fd);
	}
	if (out_fd >= 0)
	{
		dup2(out_fd, STDOUT_FILENO);
		close(out_fd);
	}
}

void	ft_haspipe(int in_fd, int out_fd, int fd1, int fd0)
{
	if (in_fd >= 0)
	{
		close(fd0);
		dup2(in_fd, STDIN_FILENO);
		close(in_fd);
		dup2(fd1, STDOUT_FILENO);
		close(fd1);
		return ;
	}
	if (in_fd == -1)
	{
		if (out_fd >= 0)
		{
			close(fd1);
			close(fd0);
			dup2(out_fd, STDOUT_FILENO);
			close(out_fd);
			return ;
		}
		close(fd0);
		dup2(fd1, STDOUT_FILENO);
		close(fd1);
		return ;
	}
}
