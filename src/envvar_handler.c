/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envvar_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunhenr <brunhenr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 14:04:17 by brunhenr          #+#    #+#             */
/*   Updated: 2024/06/11 17:26:27 by brunhenr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libs/headers.h"

t_var	*find_envvar(t_var *envvar_list, char *name)
{
	size_t		name_len;
	t_var		*current;

	if (envvar_list == NULL || name == NULL)
		return (NULL);
	name_len = ft_strlen(name);
	current = envvar_list;
	while (current != NULL)
	{
		if (current->content != NULL && \
		ft_strncmp(current->content, name, name_len - 1) == 0)
			return (current);
		current = current->next;
	}
	return (NULL);
}

void	remove_envvar(t_var **envvar_list, t_var *envvar)
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
			//free(current); ja esta sendo feito no free_shell
			return ;
		}
		prev = current;
		current = current->next;
	}
}

void	edit_envvar(t_var *envvar, char *var, char *new_value)
{
	int	len;

	len = ft_strlen(new_value) + ft_strlen(var) + 2;
	free(envvar->content);
	envvar->content = malloc(len);
	if (envvar->content != NULL)
	{
		ft_strcpy (envvar->content, var);
		ft_strcat (envvar->content, "=");
		ft_strcat(envvar->content, new_value);
	}
}

void	set_envvar(t_var **envvar_list, char *name, char *value)
{
	t_var	*envvar;
	char	*new_content;
	size_t	name_len;
	size_t	value_len;

	name_len = ft_strlen(name);
	value_len = ft_strlen(value);
	envvar = find_envvar(*envvar_list, name);
	if (envvar != NULL)
	{
		edit_envvar(envvar, name, value);
		return ;
	}
	new_content = malloc(name_len + value_len + 2);
	if (new_content == NULL)
		return ;
	ft_strcpy(new_content, name);
	new_content[name_len] = '=';
	ft_strcpy(new_content + name_len + 1, value);
	envvar = malloc(sizeof(t_var));
	if (envvar == NULL)
	{
		free(new_content);
		return ;
	}
	envvar->content = new_content;
	envvar->env = true;
	envvar->next = *envvar_list;
	*envvar_list = envvar;
}

char	*get_value(t_var *envvar_list, char *name)
{
	t_var	*envvar;
	char	*temp;

	envvar = find_envvar(envvar_list, name);
	if (envvar == NULL)
		return (NULL);
	temp = envvar->content;
	while (*temp != '=')
		temp++;
	return (temp + 1);
}
