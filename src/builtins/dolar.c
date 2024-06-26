/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dolar.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncampbel <ncampbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 14:29:05 by ncampbel          #+#    #+#             */
/*   Updated: 2024/06/26 12:04:06 by ncampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libs/headers.h"

static char *get_name(char *input, int start)
{
	int	i;
	
	i = 0;
	while (input[start + i] != '\0' && input[start + i] != ' ')
		i++;
	return (ft_substr(input, start, i));
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

void	expand_dolar(char **input, t_minishell *shell)
{
	int		i;
	t_var	*var;
	char	*var_value;
	char	*var_name;
	bool	squote;

	i = -1;
	var_value = "";
	squote = false;
	while ((*input)[++i])
	{
		if ((*input)[i] == '\'')
			squote = !squote;
		if ((*input)[i] == '$' && squote == false)
		{
			var_name = get_name((*input), i + 1);
			var = find_envvar(shell->envvars, var_name);
			if (var)
				var_value = ft_strdup(var->value);
			(*input) = ft_strreplace((*input), i, var_value);
		}
	}
}
