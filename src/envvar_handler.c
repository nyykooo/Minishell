/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envvar_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncampbel <ncampbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 14:04:17 by brunhenr          #+#    #+#             */
/*   Updated: 2024/07/30 17:31:13 by ncampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libs/headers.h"

t_var	*ft_find_envvar(t_var *envvar_list, char *name)
{
	t_var		*current;

	if (envvar_list == NULL || name == NULL)
		return (NULL);
	current = envvar_list;
	while (current != NULL)
	{
		if (current->name != NULL && \
		ft_strcmp(current->name, name) == 0)
			return (current);
		current = current->next;
	}
	return (NULL);
}

void	ft_remove_envvar(t_var **envvar_list, t_var *envvar)
{
	t_var	*current;
	t_var	*prev;

	current = *envvar_list;
	prev = NULL;
	while (current != NULL)
	{
		if (current == envvar)
		{
			if (prev == NULL)
				*envvar_list = current->next;
			else
				prev->next = current->next;
			free(current->content);
			free(current->name);
			free(current->value);
			free(current);
			return ;
		}
		prev = current;
		current = current->next;
	}
}

char	*ft_create_envvar_content(char *name, char *value)
{
	size_t name_len;
	size_t value_len;
	char	*content;

	name_len = ft_strlen(name);
	value_len = ft_strlen(value);
	content = malloc(name_len + value_len + 2);
	if (content == NULL) 
		return NULL;
	ft_strcpy(content, name);
	content[name_len] = '=';
	if (value_len > 0)
		ft_strcpy(content + name_len + 1, value);
	else
		content[name_len + 1] = '\0';
	return (content);
}

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

void set_envvar(t_var **envvar_list, char *name, char *value, int flag)
{
	t_var *envvar;
	envvar = ft_find_envvar(*envvar_list, name);
	if (envvar != NULL)
		ft_update_existing_envvar(envvar, name, value);
	else
		ft_add_new_envvar(envvar_list, name, value, flag);
}

char	*ft_get_value(t_var *envvar_list, char *name)
{
	t_var	*envvar;
	char	*temp;

	envvar = ft_find_envvar(envvar_list, name);
	if (envvar == NULL)
		return (NULL);
	temp = envvar->content;
	while (*temp != '=')
		temp++;
	return (temp + 1);
}
