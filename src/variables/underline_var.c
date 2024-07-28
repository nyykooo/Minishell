/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   underline_var.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncampbel <ncampbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 22:12:28 by ncampbel          #+#    #+#             */
/*   Updated: 2024/07/28 22:25:28 by ncampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libs/headers.h"

void	ft_update_underlinevar(t_minishell *shell)
{
	t_cmd	*current;
	t_arg	*arg;
	t_var	*underlinevar;
	char	*underlinevar_value;

	current = shell->commands;
	while (current->next)
		current = current->next;
	if (!current->arguments)
	{
		if (current->path)
			underlinevar_value = ft_strdup(current->path);
		else
			underlinevar_value = ft_strdup(current->cmd);
	}
	else
	{
		arg = current->arguments;
		while (arg->next)
			arg = arg->next;
		underlinevar_value = ft_strdup(arg->arg);
	}
	underlinevar = find_envvar(shell->envvars, "_");
	update_existing_envvar(underlinevar, "_", underlinevar_value);
	free(underlinevar_value);
}

void	ft_set_underline(t_var **envvar)
{
	t_var	*node;

	node = find_envvar(*envvar, "_");
	if (!node)
		add_new_envvar(envvar, "_", "./minishell", 1);
	else
		update_existing_envvar(node, "_", "./minishell");
	if (!node)
		return ;
	node->exp = false;
}
