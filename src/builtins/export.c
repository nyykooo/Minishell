/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunhenr <brunhenr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 16:33:57 by brunhenr          #+#    #+#             */
/*   Updated: 2024/06/12 16:34:58 by brunhenr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libs/headers.h"

static void	handle_export_args(/*t_var *envvar_list*/ t_minishell *shell)
{
	//t_var	*current;
	int		i;

	i = 1;
	while ((*shell->tokens)->argument[i]->arg != NULL)
	{
		printf("OK! argument %d: %s\n", i, (*shell->tokens)->argument[i]->arg);
		i++;	
	}
}

void	handle_export(t_var *envvar_list, t_minishell *shell)
{
	t_var	*current;

	//printf("arguments: %s\n", (*shell->tokens)->argument[0]->arg);
	//printf("arguments: %s\n", (*shell->tokens)->argument[1]->arg);
	//printf("arguments: %s\n", (*shell->tokens)->argument[2]->arg);
	if ((*shell->tokens)->argument[1]->arg == NULL)
	{
		current = envvar_list;
		while (current != NULL)
		{
			//incluir o valor entre aspas duplas
			if (current->exp == true)
				printf("declare -x %s\n", current->content);
			current = current->next;
		}
	}
	else
		handle_export_args(shell);
}