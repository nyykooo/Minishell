/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   equal.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncampbel <ncampbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 13:24:08 by ncampbel          #+#    #+#             */
/*   Updated: 2024/06/05 20:45:49 by ncampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libs/headers.h"

static void ft_varadd_back(t_var **lst, t_var *new)
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

void	handle_equal(t_minishell *shell, t_token *token)
{
	t_var *new_var;
	
	new_var = malloc(sizeof(t_var));
	if (new_var == NULL)
	{
		write(2, "Error: malloc failed\n", 21);
		return ;
	}
	new_var->content = ft_strdup(token->argument[0]);
	new_var->env = false;
	ft_varadd_back(&shell->envvars, new_var);
}
