/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunhenr <brunhenr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 14:11:44 by ncampbel          #+#    #+#             */
/*   Updated: 2024/08/09 11:33:19 by brunhenr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libs/headers.h"

void	ft_handle_pwd(t_minishell *shell)
{
	char	*pwd;

	pwd = ft_find_envvar(shell->envvars, "PWD")->content + 4;
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
