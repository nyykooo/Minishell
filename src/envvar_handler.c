/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envvar_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncampbel <ncampbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 14:04:17 by brunhenr          #+#    #+#             */
/*   Updated: 2024/06/22 15:33:44 by ncampbel         ###   ########.fr       */
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
	if (envvar->content == NULL)
		return ;
	
		ft_strcpy (envvar->content, var);
		ft_strcat (envvar->content, "=");
		ft_strcat(envvar->content, new_value);
}

char	*create_envvar_content(char *name, char *value)
{
	size_t name_len;
	size_t value_len;
	char	*content;

	name_len = ft_strlen(name);
	value_len = ft_strlen(value);
	content = malloc(name_len + value_len + 2);
	if (content == NULL) 
		return NULL;
	strcpy(content, name);
	content[name_len] = '=';
	strcpy(content + name_len + 1, value);
	return (content);
}
static void	update_existing_envvar(t_var *envvar, char *name, char *value)
{
	free(envvar->name);
	free(envvar->value);
	free(envvar->content);
	envvar->name = strdup(name);
	envvar->value = strdup(value);
	envvar->content = create_envvar_content(name, value);
}

static void add_new_envvar(t_var **envvar_list, char *name, char *value)
{
	t_var	*envvar;

	envvar = malloc(sizeof(t_var));
	if (envvar == NULL)
		return;
	envvar->content = create_envvar_content(name, value);
	if (envvar->content == NULL)
	{
		free(envvar);
		return;
	}
	envvar->env = true;
	envvar->exp = true;
	envvar->name = strdup(name);
	envvar->value = strdup(value);
	envvar->next = *envvar_list;
	*envvar_list = envvar;
}
void set_envvar(t_var **envvar_list, char *name, char *value)
{
	t_var *envvar;
	envvar = find_envvar(*envvar_list, name);
	if (envvar != NULL)
		update_existing_envvar(envvar, name, value);
	else
		add_new_envvar(envvar_list, name, value);
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
