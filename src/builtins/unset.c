/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunhenr <brunhenr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 17:09:55 by brunhenr          #+#    #+#             */
/*   Updated: 2024/08/09 11:33:11 by brunhenr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libs/headers.h"

void	ft_handle_unset(t_cmd *command, t_var **envvar_list)
{
	t_var	*envvar;
	t_arg	*temp;

	if (command->arguments == NULL)
		return ;
	temp = command->arguments;
	if (ft_check_options(temp))
		return ;
	while (temp != NULL)
	{
		envvar = ft_find_envvar(*envvar_list, temp->arg);
		if (envvar != NULL)
			ft_remove_envvar(envvar_list, envvar);
		temp = temp->next;
	}
}
