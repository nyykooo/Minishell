/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncampbel <ncampbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 10:27:00 by ncampbel          #+#    #+#             */
/*   Updated: 2024/06/22 16:22:20 by ncampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libs/headers.h"

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
	return (head);
}
