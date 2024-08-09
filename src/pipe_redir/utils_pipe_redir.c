/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pipe_redir.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunhenr <brunhenr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 16:59:15 by brunhenr          #+#    #+#             */
/*   Updated: 2024/08/09 17:08:09 by brunhenr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libs/headers.h"

bool	ft_is_pipe_or_redir(t_cmd *cmd, int i)
{
	if (i == 0 && cmd->type == T_RTRUNC)
		return (true);
	if (cmd->type == T_RTRUNC && cmd->prev->type == T_PIPE)
		return (false);
	if (cmd->type == T_RAPEND || cmd->type == T_RTRUNC || \
	cmd->type == T_LTRUNC || cmd->type == T_LAPEND || \
	cmd->type == T_PIPE)
		return (true);
	return (false);
}

bool	ft_is_file(t_cmd *cmd)
{
	if (cmd->prev != NULL && (cmd->prev->type == T_RAPEND || \
	cmd->prev->type == T_RTRUNC || \
	cmd->prev->type == T_LTRUNC || \
	cmd->prev->type == T_LAPEND))
	{
		printf("fdfadfad\n");
		return (true);
	}
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
