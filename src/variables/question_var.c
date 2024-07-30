/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   question_var.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncampbel <ncampbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 22:16:41 by ncampbel          #+#    #+#             */
/*   Updated: 2024/07/30 17:29:33 by ncampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libs/headers.h"

void	ft_update_questionvar(t_minishell *shell)
{
	t_var	*questionvar;
	char	*questionvar_value;

	questionvar = ft_find_envvar(shell->envvars, "?");
	questionvar_value = ft_itoa(shell->exit_status);
	ft_update_existing_envvar(questionvar, "?", questionvar_value);
	free(questionvar_value);
}

void	ft_create_questionvar(t_var **envvar)
{
	t_var	*new_node;
	char	*questionvar;

	new_node = ft_calloc(1, sizeof(t_var));
	questionvar = ft_itoa(0);
	new_node->content = ft_strjoin("?=", questionvar);
	new_node->name = ft_strdup("?");
	new_node->value = ft_strdup(questionvar);
	ft_varadd_back(envvar, new_node);
	free(questionvar);
}
