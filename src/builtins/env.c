/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncampbel <ncampbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 17:06:53 by brunhenr          #+#    #+#             */
/*   Updated: 2024/06/18 14:07:26 by ncampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libs/headers.h"

void	handle_env(t_var *envvar_list, t_minishell *shell)
{
	t_var	*current;

	//erro free(): invalid pointer - conforme o tamanho do input
	if (shell->commands->arguments != NULL)
	{
		printf("env: %s: No such file or directory\n", \
		shell->commands->arguments->arg);
		return ;
	}
	current = envvar_list;
	while (current != NULL)
	{
		if (current->env == true)
			printf("%s\n", current->content);
		current = current->next;
	}
}
