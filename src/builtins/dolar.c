/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dolar.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncampbel <ncampbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 14:29:05 by ncampbel          #+#    #+#             */
/*   Updated: 2024/06/10 20:11:03 by ncampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libs/headers.h"

static char *ft_strreplace(char *src, int i, char *insert)
{
	char	*new;
	int		del_len;
	int		insert_len;

	if (!src || !insert)
		return (NULL);
	insert_len = ft_strlen(insert);
	del_len = 0;
	while (src[i + del_len] && src[i + del_len] != ' ')
		del_len++;
	new = (char *)malloc(sizeof(char) * (ft_strlen(src) - del_len + insert_len + 1));
	if (!new)
		return (NULL);
	ft_strlcpy(new, src, i);
	ft_strlcpy(new + i, insert, insert_len);
	ft_strlcpy(new + i + insert_len, src + i + del_len, ft_strlen(src) - del_len);
	free(src);
	return (new);
}

//ft_strnstr

static void *expand_argument(t_arg *argument, t_minishell *shell)
{
	int	i;
	t_var *var;
	char *var_value;
	int j;

	i = -1;
	var_value = "";
	while (argument->arg[++i])
	{
		if (argument->arg[i] == N_DOLLAR)
		{
			var = find_envvar(shell->envvars, argument->arg + i + 1);
			j = -1;
			while (var->content[++j] && var->content[j] != '=')
				;
			if (var->content[j] == '=')
				var_value = ft_substr(var->content, j + 1, ft_strlen(var->content) - j - 1);
			argument->arg = ft_strreplace(argument->arg, i, var_value);
		}
	}
	return (argument->arg);
}

void	expand_dolar(t_arg *argument , t_minishell *shell)
{
	if (argument->arg)
	{
		if (argument->dol && ((!argument->sq && !argument->dq)
			|| argument->dq))
			expand_argument(argument, shell);
	}
}