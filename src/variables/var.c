/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncampbel <ncampbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 10:27:00 by ncampbel          #+#    #+#             */
/*   Updated: 2024/07/02 22:04:21 by ncampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libs/headers.h"

void	update_underlinevar(t_minishell *shell)
{
	t_cmd	*current;
	t_arg	*arg;
	t_var	*underlinevar;
	char	*underlinevar_value;

	current = shell->commands;
	while (current->next)
		current = current->next;
	if (!current->arguments)
		underlinevar_value = ft_strdup(current->cmd);
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

void	update_vars(t_minishell *shell)
{
	update_questionvar(shell);
	update_underlinevar(shell);
}

void	update_questionvar(t_minishell *shell)
{
	t_var	*questionvar;
	char	*questionvar_value;

	questionvar = find_envvar(shell->envvars, "?");
	questionvar_value = ft_itoa(shell->exit_status);
	update_existing_envvar(questionvar, "?", questionvar_value);
	free(questionvar_value);
}

static void	create_questionvar(t_var *envvar)
{
	t_var	*new_node;
	char	*questionvar;

	new_node = ft_calloc(1, sizeof(t_var));
	questionvar = ft_itoa(0);
	new_node->content = ft_strjoin("?=", questionvar);
	new_node->name = ft_strdup("?");
	new_node->value = ft_strdup(questionvar);
	ft_varadd_back(&envvar, new_node);
}

static void	set_underline(t_var *envvar)
{
	t_var	*node;

	node = find_envvar(envvar, "_");
	if (!node)
		return ;
	node->exp = false;
}

t_var *create_list(char **envp)
{
	char	**current;
	t_var	*new_node;
	t_var	*head;
	char	*shlvl_value;

	head = NULL;
	current = envp;
	while (*current)
	{
		new_node = ft_calloc(1, sizeof(t_var));
		new_node->content = ft_strdup(*current);
		new_node->name = ft_strndup(*current, ft_strchr(*current, '=') - *current);
		new_node->value = ft_strdup(ft_strchr(*current, '=') + 1);
		new_node->env = true;
		new_node->exp = true;
		ft_varadd_back(&head, new_node);
		current++;
		if (ft_strcmp(new_node->name, "SHLVL") == 0)
		{
			shlvl_value = ft_itoa(ft_atoi(new_node->value) + 1);
			update_existing_envvar(new_node, "SHLVL", shlvl_value);
		}
	}
	create_questionvar(head);
	set_underline(head);
	return (head);
}
