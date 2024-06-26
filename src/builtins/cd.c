/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncampbel <ncampbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 14:36:28 by brunhenr          #+#    #+#             */
/*   Updated: 2024/06/26 13:22:54 by ncampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libs/headers.h"

static void	 change_directory(char *dir, int should_free)
{
	char	*error;

	if (chdir(dir) == -1)
	{
		error = error_msg_construct(4, "-minishell: cd: ", dir, ": ", "No such file or directory\n");
		put_error_msg(error, 1);
		free(error);
	}
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

// dar um jeito de criar a variavel caso ela nao exista

void	pwds_update(t_var **envvar_list, char *dir)
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
		set_envvar(envvar_list, "OLDPWD", pwd, 1); // oldpwd deve ir para env se nao existe enquanto a pwd nao deve ir
		return ;
	}
	oldpwd = get_value(*envvar_list, "PWD");
	if (oldpwd != NULL)
		set_envvar(envvar_list, "OLDPWD", oldpwd, 1);
	set_envvar(envvar_list, "PWD", pwd, 0);
	free(pwd);
}

void	handle_cd(t_cmd *command, t_minishell *shell)
{
	char	*dir;
	int		should_free;

	dir = NULL;
	should_free = 0;
	if (ft_argsize(command->arguments) >= 2)
	{
		write(2, "-minishell: cd: too many arguments\n", 36);
		return ;
	}
	else if (command->arguments == NULL || \
	ft_strcmp(command->arguments->arg, "--") == 0 || \
	ft_strcmp(command->arguments->arg, "~") == 0)
	{
		dir = get_value(shell->envvars, "HOME");
		if (dir == NULL)
		{
			write(2, "cd: HOME not set\n", 17);
			return ;
		}
	}
	else if (command->arguments->arg != NULL && command->arguments->next == NULL)
		dir = get_dir(command->arguments->arg, &should_free, shell->envvars);
	if (dir != NULL)
		change_directory(dir, should_free);
	pwds_update(&shell->envvars, dir);
}
