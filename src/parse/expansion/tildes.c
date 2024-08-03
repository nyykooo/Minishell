/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tildes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncampbel <ncampbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 18:50:43 by ncampbel          #+#    #+#             */
/*   Updated: 2024/08/03 11:46:42 by ncampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../libs/headers.h"

static char	*ft_strreplace_tilde(char *src, int i, char *insert, char *name)
{
	char	*str_frag;
	char	*tmp;
	char	*new;

	str_frag = ft_substr(src, 0, i);
	tmp = ft_strjoin(str_frag, insert);
	new = ft_strjoin(tmp, src + i + ft_strlen(name));
	free(str_frag);
	free(tmp);
	free(src);
	return (new);
}

void	expand_tildes(char **input, t_minishell *shell)
{
	int		i;
	t_var	*var;
	char	*var_value;

	i = -1;
	var_value = "";
	while ((*input)[++i])
	{
		if ((*input)[i] == '~' && ft_is_inside_quotes((*input), i) == 0 && (*input)[i - 1] == ' ' &&
			((*input)[i + 1] == ' ' || (*input)[i + 1] == '\0'
			|| (*input)[i + 1] == '/'))
		{
			var = ft_find_envvar(shell->envvars, "HOME");
			if (var)
				var_value = ft_strdup(var->value);
			(*input) = ft_strreplace_tilde((*input), i, var_value, "~");
		}
	}
}