/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncampbel <ncampbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 22:13:47 by ncampbel          #+#    #+#             */
/*   Updated: 2024/08/05 22:15:04 by ncampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../libs/headers.h"

void	ft_swap_nodes(t_var *a, t_var *b)
{
	char	*temp_content;
	char	*temp_name;
	char	*temp_value;
	bool	temp_exp;
	bool	temp_env;

	temp_content = a->content;
	temp_name = a->name;
	temp_value = a->value;
	temp_exp = a->exp;
	temp_env = a->env;
	a->content = b->content;
	a->name = b->name;
	a->value = b->value;
	a->exp = b->exp;
	a->env = b->env;
	b->content = temp_content;
	b->name = temp_name;
	b->value = temp_value;
	b->exp = temp_exp;
	b->env = temp_env;
}

void	ft_sort_content(t_var *envvar)
{
	t_var			*temp;
	t_var			*last_verified;
	int				swapped;

	swapped = 1;
	last_verified = NULL;
	if (envvar == NULL)
		return ;
	while (swapped)
	{
		swapped = 0;
		temp = envvar;
		while (temp->next != last_verified)
		{
			if (ft_strcmp(temp->content, temp->next->content) > 0)
			{
				ft_swap_nodes(temp, temp->next);
				swapped = 1;
			}
			temp = temp->next;
		}
		last_verified = temp;
	}
}
