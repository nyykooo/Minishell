/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define_in_out_fd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncampbel <ncampbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 19:50:15 by ncampbel          #+#    #+#             */
/*   Updated: 2024/08/09 19:51:18 by ncampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libs/headers.h"

static void	ft_add_argument(t_arg **main_cmd_args, t_arg *new_node)
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

static void	ft_in_fd(int *in_fd, t_cmd *current_cmd)
{
	char	*error_msg;

	if (*in_fd >= 0)
		close(*in_fd);
	*in_fd = open(current_cmd->cmd, O_RDONLY);
	if (*in_fd < 0)
	{
		if (current_cmd->prev->prev != NULL)
		{
			open(current_cmd->prev->prev->cmd, O_WRONLY | O_TRUNC \
			| O_CREAT, 0644);
		}
		error_msg = ft_error_msg_construct(5, "-minishell: ", \
		current_cmd->cmd, ": ", strerror(errno), "\n");
		exit (ft_put_error_msg(error_msg, 1));
	}
	ft_add_argument(&current_cmd->prev->prev->arguments, \
	current_cmd->arguments);
	while (current_cmd->arguments)
	{
		*in_fd = open(current_cmd->arguments->arg, O_RDONLY);
		current_cmd->arguments = current_cmd->arguments->next;
	}
}

static int	ft_determine_flags(t_cmd *cmd_temp)
{
	int	flags;

	flags = O_WRONLY | O_CREAT;
	if (cmd_temp->rappend == true)
		flags |= O_APPEND;
	else
		flags |= O_TRUNC;
	return (flags);
}

static void	ft_out_fd(int *out_fd, t_cmd *current_cmd)
{
	int	flags;

	flags = ft_determine_flags(current_cmd);
	if (*out_fd >= 0)
		close(*out_fd);
	*out_fd = open(current_cmd->cmd, flags, 0644);
	if (*out_fd < 0)
	{
		perror("open");
		exit(1);
	}
	if (current_cmd->prev->prev != NULL && \
	current_cmd->arguments != NULL)
		ft_add_argument(&current_cmd->prev->prev->arguments, \
		current_cmd->arguments);
}

void	ft_define_in_out_fd(t_cmd *cmd_temp, int *in_fd, int *out_fd)
{
	t_cmd	*current_cmd;

	*in_fd = -1;
	*out_fd = -1;
	current_cmd = cmd_temp;
	while (current_cmd != NULL && current_cmd->type != T_PIPE)
	{
		if (current_cmd->input_file == true)
			ft_in_fd(in_fd, current_cmd);
		if (current_cmd->type == T_LAPEND)
		{
			if (*in_fd >= 0)
				close(*in_fd);
			if (current_cmd->prev)
				*in_fd = current_cmd->prev->here_doc_fd;
		}
		if (current_cmd->rappend == true || current_cmd->rtrunc == true)
			ft_out_fd(out_fd, current_cmd);
		current_cmd = current_cmd->next;
	}
}
