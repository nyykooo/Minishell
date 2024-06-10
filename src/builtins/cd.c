/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncampbel <ncampbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 14:36:28 by brunhenr          #+#    #+#             */
/*   Updated: 2024/06/10 16:49:18 by ncampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libs/headers.h"

static void	change_directory(char *dir, int should_free)
{
	if (chdir(dir) == -1)
		write(2, "cd: no such file or directory\n", 30);
	if (should_free == 1)
		free(dir);
}

static char	*get_dir(char *arg, int *should_free, t_var *envvar_list)
{
	char	*dir;

	dir = NULL;
	if (ft_strcmp(arg, "-") == 0)
	{
		dir = get_value(envvar_list, "OLDPWD");
		if (dir == NULL)
		{
			write(2, "cd: OLDPWD not set\n", 19);
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

void	pwds_update(t_var *envvar_list, char *dir)
{
	char	*pwd;
	char	*oldpwd;

	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
	{
		write(2, "cd: error retrieving current directory using getcwd\n", 53);
		return ;
	}
	if (ft_strcmp(dir, ".") == 0)
	{
		set_envvar(&envvar_list, "OLDPWD", pwd);
		return ;
	}
	oldpwd = get_value(envvar_list, "PWD");
	if (oldpwd != NULL)
		set_envvar(&envvar_list, "OLDPWD", oldpwd);
	set_envvar(&envvar_list, "PWD", pwd);
	free(pwd);
}

void	handle_cd(t_token **tokens, t_minishell *shell)
{
	char	*dir;
	int		should_free;

	dir = NULL;
	should_free = 0;
	if (tokens[0]->argument[1]->arg != NULL && tokens[0]->argument[2]->arg != NULL)
	{
		write(2, "cd: too many arguments\n", 24);
		return ;
	}
	else if (tokens[0]->argument[1] == NULL || \
	ft_strcmp(tokens[0]->argument[1]->arg, "--") == 0)
	{
		dir = get_value(shell->envvars, "HOME");
		if (dir == NULL)
		{
			write(2, "cd: HOME not set\n", 17);
			return ;
		}
	}
	else if (tokens[0]->argument[1]->arg != NULL && tokens[0]->argument[2]->arg == NULL)
		dir = get_dir(tokens[0]->argument[1]->arg, &should_free, shell->envvars);
	if (dir != NULL)
		change_directory(dir, should_free);
	pwds_update(shell->envvars, dir);
}
