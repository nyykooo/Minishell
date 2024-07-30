/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tildes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncampbel <ncampbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 18:50:43 by ncampbel          #+#    #+#             */
/*   Updated: 2024/07/30 19:02:52 by ncampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../libs/headers.h"

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
			(*input) = ft_strreplace((*input), i, var_value, "~");
		}
	}
}