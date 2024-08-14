/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncampbel <ncampbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 14:36:28 by brunhenr          #+#    #+#             */
/*   Updated: 2024/08/15 00:33:00 by ncampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libs/headers.h"

static char	*get_dir(char *arg, int *should_free, t_var *envvar_list)
{
	char	*dir;

	dir = NULL;
	if (ft_strcmp(arg, "-") == 0)
	{
		dir = ft_get_value(envvar_list, "OLDPWD");
		if (dir == NULL)
		{
			ft_print_error(false, 3, 1,
				"-minishell: cd: no OLDPWD\n");
			return (NULL);
		}
	}
	else
	{
		dir = ft_strdup(arg);
		*should_free = 1;
	}
	return (dir);
}

void	pwds_update(t_var **envvar_list, char *dir)
{
	char	*pwd;
	char	*oldpwd;

	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
	{
		ft_print_error(false, 3, 1,
			"cd: error retrieving current directory using getcwd\n");
		return ;
	}
	if (ft_strcmp(dir, ".") == 0)
	{
		ft_set_envvar(envvar_list, "OLDPWD", pwd, 1);
		free(pwd);
		return ;
	}
	oldpwd = ft_get_value(*envvar_list, "PWD");
	if (oldpwd != NULL)
		ft_set_envvar(envvar_list, "OLDPWD", oldpwd, 1);
	ft_set_envvar(envvar_list, "PWD", pwd, 0);
	free(pwd);
}

static void	change_directory(char *dir, int should_free, t_minishell *shell)
{
	struct stat	buf;

	if (dir && dir[0] != 0 && chdir(dir) == -1)
	{
		if (stat(dir, &buf) == 0)
		{
			if ((buf.st_mode & __S_IFREG))
				ft_print_error(false, 1, 3,
					"-minishell: cd: ", dir, ": Not a directory\n");
		}
		else
			ft_print_error(false, 1, 3,
			"-minishell: cd: ", dir, ": No such file or directory\n");
	}
	else
		pwds_update(&shell->envvars, dir);
	if (should_free == 1)
		free(dir);
}

void	ft_handle_cd(t_cmd *command, t_minishell *shell)
{
	char	*dir;
	int		should_free;

	dir = NULL;
	should_free = 0;
	if (ft_argsize(command->arguments) >= 2)
		ft_print_error(false, 1, 3,
			"-minishell: ", command->cmd, ": too many arguments\n");
	else if (command->arguments == NULL || \
	ft_strcmp(command->arguments->arg, "--") == 0)
	{
		dir = ft_get_value(shell->envvars, "HOME");
		if (dir == NULL)
			ft_print_error(false, 1, 1,
				"-minishell: cd: HOME not set\n");
	}
	else if (command->arguments->arg != NULL
		&& command->arguments->next == NULL)
		dir = get_dir(command->arguments->arg, &should_free, shell->envvars);
	if (dir != NULL)
		change_directory(dir, should_free, shell);
	else
		shell->exit_status = 1;
}
