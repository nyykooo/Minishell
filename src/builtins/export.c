/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncampbel <ncampbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 16:33:57 by brunhenr          #+#    #+#             */
/*   Updated: 2024/06/16 17:38:35 by ncampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libs/headers.h"

static void	handle_export_args(/*t_var *envvar_list*/ t_minishell *shell)
{
	//t_var	*current;
	t_arg *temp;
	int i;

	i = 0;
	temp = shell->commands->arguments;
	while (temp->arg != NULL)
	{
		printf("OK! argument %d: %s\n", i++, temp->arg);
		temp = temp->next;
	}
}

void	handle_export(t_var *envvar_list, t_minishell *shell)
{
	t_var	*current;
	t_arg *temp;

	temp = shell->commands->arguments;
	//printf("arguments: %s\n", (*shell->tokens)->argument[0]->arg);
	//printf("arguments: %s\n", (*shell->tokens)->argument[1]->arg);
	//printf("arguments: %s\n", (*shell->tokens)->argument[2]->arg);
	if (temp == NULL)
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