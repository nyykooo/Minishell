/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_operations2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncampbel <ncampbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 18:36:36 by ncampbel          #+#    #+#             */
/*   Updated: 2024/07/30 18:37:28 by ncampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libs/headers.h"

void	ft_update_existing_envvar(t_var *envvar, char *name, char *value)
{
	free(envvar->name);
	free(envvar->value);
	free(envvar->content);
	envvar->name = ft_strdup(name);
	envvar->value = ft_strdup(value);
	envvar->content = ft_create_envvar_content(name, value);
}

void ft_add_new_envvar(t_var **envvar_list, char *name, char *value, int flag)
{
	t_var	*envvar;

	envvar = ft_calloc(1, sizeof(t_var));
	if (!envvar)
		return;
	envvar->content = ft_create_envvar_content(name, value);
	if (envvar->content == NULL)
	{
		free(envvar);
		return;
	}
	if (flag == 1)
	{
		envvar->env = true;
		envvar->exp = true;	
	}
	envvar->name = strdup(name);
	envvar->value = strdup(value);
	ft_varadd_back(envvar_list, envvar);
}

void ft_set_envvar(t_var **envvar_list, char *name, char *value, int flag)
{
	t_var *envvar;
	envvar = ft_find_envvar(*envvar_list, name);
	if (envvar != NULL)
		ft_update_existing_envvar(envvar, name, value);
	else
		ft_add_new_envvar(envvar_list, name, value, flag);
}