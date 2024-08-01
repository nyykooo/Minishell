/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncampbel <ncampbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 17:06:53 by brunhenr          #+#    #+#             */
/*   Updated: 2024/08/01 16:27:22 by ncampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libs/headers.h"

void	handle_env(t_var *envvar_list, t_minishell *shell, t_cmd *command)
{
	t_var	*current;
	char	*error;

	if (command->arguments != NULL)
	{
		// ft_print_error_and_free(shell, false, 127, 3, "env: ", command->arguments->arg, ": No such file or directory\n");
		error = error_msg_construct(3, "env: `", command->arguments->arg, "`: No such file or directory\n");
		shell->exit_status = put_error_msg(error, 127);
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
