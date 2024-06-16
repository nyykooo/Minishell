/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncampbel <ncampbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 17:09:55 by brunhenr          #+#    #+#             */
/*   Updated: 2024/06/16 17:51:25 by ncampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libs/headers.h"

void	handle_unset(t_cmd *command, t_var **envvar_list)
{
	t_var	*envvar;
	t_arg	*temp;

	if (command->arguments->arg == NULL)
		return ;
	temp = command->arguments;
	while (temp != NULL)
	{
		envvar = find_envvar(*envvar_list, temp->arg);
		if (envvar != NULL)
			remove_envvar(envvar_list, envvar);
	}
}