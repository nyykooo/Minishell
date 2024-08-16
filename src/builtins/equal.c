/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   equal.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncampbel <ncampbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 13:24:08 by ncampbel          #+#    #+#             */
/*   Updated: 2024/08/16 15:36:45 by ncampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libs/headers.h"

bool	ft_check_equal(t_token *token)
{
	int	i;

	i = -1;
	while (token->content[++i])
	{
		if (token->content[i] == EQUAL)
			return (true);
	}
	return (false);
}

static void	ft_handle_equal_cmd(t_minishell *shell, t_cmd *command)
{
	t_var	*var;
	char	*name;
	char	*value;
	int		equal;

	equal = 0;
	while (command->cmd[equal] != '=')
		equal++;
	name = ft_substr(command->cmd, 0, equal);
	value = ft_substr(command->cmd, equal + 1,
			ft_strlen(command->cmd) - equal - 1);
	var = ft_find_envvar(shell->envvars, name);
	if (var)
	{
		ft_set_envvar(&shell->envvars, name, value, 1);
		free(value);
		free(name);
		return ;
	}
	ft_set_envvar(&shell->envvars, name, value, 0);
	free(name);
	free(value);
}

static void	ft_handle_equal_arg(t_minishell *shell, t_arg *arg)
{
	t_var	*var;
	char	*name;
	char	*value;
	int		equal;

	equal = 0;
	while (arg->arg[equal] != '=')
		equal++;
	name = ft_substr(arg->arg, 0, equal);
	value = ft_substr(arg->arg, equal + 1,
			ft_strlen(arg->arg) - equal - 1);
	var = ft_find_envvar(shell->envvars, name);
	if (var)
	{
		ft_set_envvar(&shell->envvars, name, value, 1);
		free(value);
		free(name);
		return ;
	}
	ft_set_envvar(&shell->envvars, name, value, 0);
	free(name);
	free(value);
}

void	ft_handle_equal_loop(t_minishell *shell, t_cmd *command)
{
	t_cmd	*tmp_cmd;
	t_arg	*tmp_arg;

	tmp_cmd = command;
	tmp_arg = NULL;
	if (command->arguments)
		tmp_arg = command->arguments;
	while (tmp_cmd && tmp_cmd->type == T_EQUAL)
	{
		ft_handle_equal_cmd(shell, tmp_cmd);
		while (tmp_arg && tmp_arg->equal)
		{
			ft_handle_equal_arg(shell, tmp_arg);
			tmp_arg = tmp_arg->next;
		}
		tmp_cmd = tmp_cmd->next;
	}
}
