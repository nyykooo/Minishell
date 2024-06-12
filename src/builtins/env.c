/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunhenr <brunhenr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 17:06:53 by brunhenr          #+#    #+#             */
/*   Updated: 2024/06/12 17:08:07 by brunhenr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libs/headers.h"

void	handle_env(t_var *envvar_list, t_minishell *shell)
{
	t_var	*current;

	//erro free(): invalid pointer - conforme o tamanho do input
	if (shell->tokens[0]->argument[1]->arg != NULL)
	{
		printf("env: %s: No such file or directory\n", \
		shell->tokens[0]->argument[1]->arg);
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
