/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   equal.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncampbel <ncampbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 13:24:08 by ncampbel          #+#    #+#             */
/*   Updated: 2024/06/16 16:41:37 by ncampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libs/headers.h"

// parsing do igual vai precisar atuar um pouco diferente do antigo

void	handle_equal(t_minishell *shell, t_cmd *command)
{
	t_var	*new_var;
	
	new_var = malloc(sizeof(t_var));
	if (new_var == NULL)
	{
		write(2, "Error: malloc failed\n", 21);
		return ;
	}
	new_var->content = ft_strdup(command->arguments->arg);
	new_var->env = false;
	ft_varadd_back(&shell->envvars, new_var);
}
