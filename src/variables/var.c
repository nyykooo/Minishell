/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncampbel <ncampbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 10:27:00 by ncampbel          #+#    #+#             */
/*   Updated: 2024/08/15 15:02:09 by ncampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libs/headers.h"

static void	ft_set_pwd(t_var **envvar)
{
	t_var	*node;
	char	*pwd;

	node = ft_find_envvar(*envvar, "PWD");
	if (!node)
	{
		pwd = getcwd(NULL, 0);
		ft_add_new_envvar(envvar, "PWD", pwd, 1);
		free(pwd);
	}
}

static void	ft_set_shlvl(t_var **envvar)
{
	t_var	*node;
	char	*shlvl_value;

	node = ft_find_envvar(*envvar, "SHLVL");
	if (node)
	{
		shlvl_value = ft_itoa(ft_atoi(node->value) + 1);
		if (ft_atoi(shlvl_value) < 0)
			shlvl_value = ft_strdup("0");
		else
		if (ft_atoi(shlvl_value) > 1000)
		{
			ft_print_error(false, 0, 3, "minishell: warning: shell level (", \
			shlvl_value, ") too high, resetting to 1\n");
			shlvl_value = ft_strdup("1");
		}
		ft_update_existing_envvar(node, "SHLVL", shlvl_value);
	}
	else
	{
		shlvl_value = ft_strdup("1");
		ft_add_new_envvar(envvar, "SHLVL", shlvl_value, 1);
	}
	free(shlvl_value);
}

static t_var	*ft_create_list(char **envp)
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
		new_node->name = ft_strndup(*current,
				ft_strchr(*current, '=') - *current);
		new_node->value = ft_strdup(ft_strchr(*current, '=') + 1);
		new_node->env = true;
		new_node->exp = true;
		ft_varadd_back(&head, new_node);
		current++;
	}
	return (head);
}

t_var	*ft_create_envvar_list(char **envp)
{
	t_var	*envvar;

	if (envp)
		envvar = ft_create_list(envp);
	else
		envvar = NULL;
	ft_create_questionvar(&envvar);
	ft_set_underline(&envvar);
	ft_set_shlvl(&envvar);
	ft_set_pwd(&envvar);
	return (envvar);
}
