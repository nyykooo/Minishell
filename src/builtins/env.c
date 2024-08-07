/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncampbel <ncampbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 17:06:53 by brunhenr          #+#    #+#             */
/*   Updated: 2024/08/06 16:51:31 by ncampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libs/headers.h"

void	handle_env(t_var *envvar_list, t_cmd *command)
{
	t_var	*current;

	if (command->arguments != NULL)
	{
		ft_print_error(false, 127, 3,
			"env: ", command->arguments->arg, ": No such file or directory\n");
		return ;
	}
	current = envvar_list;
	while (current != NULL)
	{
		if (current->env == true && current->value != NULL)
			printf("%s\n", current->content);
		current = current->next;
	}
}
