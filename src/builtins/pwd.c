/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncampbel <ncampbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 14:11:44 by ncampbel          #+#    #+#             */
/*   Updated: 2024/08/15 18:19:33 by ncampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libs/headers.h"

void	ft_handle_pwd(t_minishell *shell)
{
	t_var	*pwd_envvar;
	char	*pwd;

	pwd_envvar = ft_find_envvar(shell->envvars, "PWD");
	if (pwd_envvar != NULL)
	{
		printf("%s\n", pwd_envvar->value);
		shell->exit_status = 0;
		return ;
	}
	else if (pwd_envvar == NULL)
	{
		pwd = getcwd(NULL, 0);
		if (pwd == NULL)
		{
			perror("minishell");
			return ;
		}
		printf("%s\n", pwd);
		free(pwd);
		shell->exit_status = 0;
	}
}
