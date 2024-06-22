/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncampbel <ncampbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 14:11:22 by ncampbel          #+#    #+#             */
/*   Updated: 2024/06/22 15:43:57 by ncampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*curr;

	if (!new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	curr = ft_lstlast(*lst);
	curr->next = new;
}

void	ft_tokenadd_back(t_token **lst, t_token *new)
{
	t_token	*curr;

	if (!new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	curr = ft_tokenlast(*lst);
	curr->next = new;
	new->prev = curr;
}

void	ft_argadd_back(t_arg **lst, t_arg *new)
{
	t_arg	*curr;

	if (!new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	curr = ft_arglast(*lst);
	curr->next = new;
	new->prev = curr;
}

void	ft_cmdadd_back(t_cmd **lst, t_cmd *new)
{
	t_cmd	*curr;

	if (!new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	curr = ft_cmdlast(*lst);
	curr->next = new;
	new->prev = curr;
}

void	ft_varadd_back(t_var **lst, t_var *new)
{
	t_var	*curr;

	if (!new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	curr = ft_varlast(*lst);
	curr->next = new;
	new->prev = curr;
}
