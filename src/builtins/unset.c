/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncampbel <ncampbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 17:09:55 by brunhenr          #+#    #+#             */
/*   Updated: 2024/08/15 18:27:09 by ncampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libs/headers.h"

void	ft_handle_unset(t_cmd *command, t_var **envvar_list)
{
	t_var	*envvar;
	t_arg	*temp;

	command->shell->exit_status = 0;
	if (command->arguments == NULL)
		return ;
	temp = command->arguments;
	if (ft_check_options(temp))
		return ;
	while (temp != NULL)
	{
		
		envvar = ft_find_envvar(*envvar_list, temp->arg);
		if (envvar != NULL && ft_strcmp(envvar->name, "_") != 0)
			ft_remove_envvar(envvar_list, envvar);	
		temp = temp->next;
	}
}
