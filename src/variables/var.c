/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunhenr <brunhenr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 10:27:00 by ncampbel          #+#    #+#             */
/*   Updated: 2024/06/11 17:26:27 by brunhenr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libs/headers.h"

t_var *create_list(char **envp)
{
	char	**current;
	t_var	*new_node;
	t_var	*head;
	t_var	*tail;

	head = NULL;
	tail = NULL;
	current = envp;
	while (*current)
	{
		new_node = malloc(sizeof(t_var));
		new_node->content = ft_strdup(*current);
		new_node->env = true;
		new_node->exp = true;
		new_node->next = NULL;
		if (head == NULL)
			head = new_node;
		else
			tail->next = new_node;
		current++;
		tail = new_node;
	}
	return (head);
}

void ft_varadd_back(t_var **lst, t_var *new)
{
	if (!new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	while (lst)
	{
		if (!(*lst)->next)
			break ;
		(*lst) = (*lst)->next;
	}
	(*lst)->next = new;
}
