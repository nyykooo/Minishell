/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncampbel <ncampbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 14:11:44 by ncampbel          #+#    #+#             */
/*   Updated: 2024/08/13 18:33:24 by ncampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libs/headers.h"

void	ft_handle_pwd(t_minishell *shell)
{
	char	*pwd;
	t_var	*var;

	var = ft_find_envvar(shell->envvars, "PWD");
	if (var)
		pwd = var->content + 4;
	if (!var)
	{
		pwd = getcwd(NULL, 0);
		if (pwd == NULL)
		{
			perror("minishell");
			return ;
		}
	}
	printf("%s\n", pwd);
	if (!var)
		free(pwd);
}
