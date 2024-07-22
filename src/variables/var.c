/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncampbel <ncampbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 10:27:00 by ncampbel          #+#    #+#             */
/*   Updated: 2024/07/22 16:56:07 by ncampbel         ###   ########.fr       */
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
		underlinevar_value = ft_strdup(current->path);
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
}

void	update_questionvar(t_minishell *shell)
{
	t_var	*questionvar;
	char	*questionvar_value;

	questionvar = find_envvar(shell->envvars, "?");
	if (!questionvar)
	{
		printf("Error: $? not found\n");
	}
	questionvar_value = ft_itoa(shell->exit_status);
	update_existing_envvar(questionvar, "?", questionvar_value);
	free(questionvar_value);
}

static void	create_questionvar(t_var **envvar)
{
	t_var	*new_node;
	char	*questionvar;

	new_node = ft_calloc(1, sizeof(t_var));
	questionvar = ft_itoa(0);
	new_node->content = ft_strjoin("?=", questionvar);
	new_node->name = ft_strdup("?");
	new_node->value = ft_strdup(questionvar);
	ft_varadd_back(envvar, new_node);
	free(questionvar);
}

static void	set_pwd(t_var **envvar)
{
	t_var	*node;
	char	*pwd;

	node = find_envvar(*envvar, "PWD");
	if (!node)
	{
		pwd = getcwd(NULL, 0);
		add_new_envvar(envvar, "PWD", pwd, 1);
		free(pwd);
	}
}

static void	set_underline(t_var **envvar)
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

static void		set_shlvl(t_var **envvar)
{
	t_var	*node;
	char	*shlvl_value;

	node = find_envvar(*envvar, "SHLVL");
	if (node)
	{
		shlvl_value = ft_itoa(ft_atoi(node->value) + 1);
		update_existing_envvar(node, "SHLVL", shlvl_value);
	}
	else
	{	
		shlvl_value = ft_strdup("1");
		add_new_envvar(envvar, "SHLVL", shlvl_value, 1);
	}
	free(shlvl_value);
}

t_var *create_list(char **envp)
{
	char	**current;
	t_var	*new_node;
	t_var	*head;

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
	}
	return (head);
}

t_var	*create_envvar_list(char **envp)
{
	t_var	*envvar;
	
	if (envp)
		envvar = create_list(envp);
	else
		envvar = NULL;
	create_questionvar(&envvar);
	set_underline(&envvar);
	set_shlvl(&envvar);
	set_pwd(&envvar);
	return (envvar);
}
