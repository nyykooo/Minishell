/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunhenr <brunhenr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 17:09:55 by brunhenr          #+#    #+#             */
/*   Updated: 2024/06/12 17:09:59 by brunhenr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libs/headers.h"

void	handle_unset(t_token **tokens, t_var **envvar_list)
{
	t_var	*envvar;
	int		i;

	if ((*tokens)->argument[1]->arg == NULL)
		return ;
	i = 1;
	while ((*tokens)->argument[i] != NULL)
	{
		envvar = find_envvar(*envvar_list, (*tokens)->argument[i]->arg);
		if (envvar != NULL)
			remove_envvar(envvar_list, envvar);
		i++;
	}
}