/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_operations1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncampbel <ncampbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 14:04:17 by brunhenr          #+#    #+#             */
/*   Updated: 2024/08/07 16:20:31 by ncampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libs/headers.h"

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
	size_t	name_len;
	size_t	value_len;
	char	*content;

	name_len = ft_strlen(name);
	value_len = ft_strlen(value);
	content = malloc(name_len + value_len + 2);
	if (content == NULL)
		return (NULL);
	ft_strcpy(content, name);
	content[name_len] = '=';
	if (value_len > 0)
		ft_strcpy(content + name_len + 1, value);
	else
		content[name_len + 1] = '\0';
	return (content);
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
