/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncampbel <ncampbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 14:11:44 by ncampbel          #+#    #+#             */
/*   Updated: 2024/06/19 17:25:04 by ncampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libs/headers.h"

void	handle_pwd(t_minishell *shell)
{
	char	*pwd;

	pwd = find_envvar(shell->envvars, "PWD")->content + 4;
	if (pwd == NULL)
	{
		pwd = getcwd(NULL, 0);
		if (pwd == NULL)
		{
			perror("minishell");
			return ;
		}
	}
	printf("%s\n", pwd);
}