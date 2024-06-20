/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dolar.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncampbel <ncampbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 14:29:05 by ncampbel          #+#    #+#             */
/*   Updated: 2024/06/20 14:53:38 by ncampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libs/headers.h"

static char *get_name(t_arg *argument, int start)
{
	int	i;
	
	i = 0;
	while (argument->arg[start + i] != '\0' && argument->arg[start + i] != ' ')
		i++;
	return (ft_substr(argument->arg, start, i));
}

static char	*ft_strreplace(char *src, int i, char *insert)
{
	char	*new;
	int		del_len;
	int		insert_len;
	int		size;

	if (!src || !insert)
		return (NULL);
	insert_len = ft_strlen(insert);
	del_len = 0;
	while (src[i + del_len] && src[i + del_len] != ' ')
		del_len++;
	size = ft_strlen(src) - del_len + insert_len + 1;
	new = (char *)malloc(sizeof(char) * \
	(size));
	if (!new)
		return (NULL);
	ft_strlcpy(new, src, i);
	ft_strlcpy(new + i, insert, insert_len);
	ft_strlcpy(new + i + insert_len, \
	src + i + del_len, ft_strlen(src) - del_len);
	free(src);
	return (new);
}

static void	*expand_argument(t_arg *argument, t_minishell *shell)
{
	int		i;
	t_var	*var;
	char	*var_value;
	char	*var_name;

	i = -1;
	var_value = "";
	while (argument->arg[++i])
	{
		if (argument->arg[i] == N_DOLLAR)
		{
			var_name = get_name(argument, i + 1);
			var = find_envvar(shell->envvars, var_name); // problema da expansao
			if (var)
				var_value = ft_strdup(var->value);
			argument->arg = ft_strreplace(argument->arg, i, var_value);
		}
	}
	return (argument->arg);
}

void	expand_dolar(t_arg *argument, t_minishell *shell)
{
	if (argument->arg)
	{
		if (argument->dol && ((!argument->sq && !argument->dq) \
		|| argument->dq))
			expand_argument(argument, shell);
	}
}
