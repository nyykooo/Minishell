/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dolar.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncampbel <ncampbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 14:29:05 by ncampbel          #+#    #+#             */
/*   Updated: 2024/08/09 18:24:49 by ncampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../libs/headers.h"

static bool	ft_is_sep(char sep)
{
	if (sep == ' ' || sep == '\0' || sep == '"' || sep == '\''
		|| sep == '=' || sep == '/')
		return (true);
	return (false);
}

static char	*ft_get_name(char *input, int start)
{
	int	i;

	i = 0;
	if (ft_is_sep(input[start]) == true)
		return (NULL);
	if (input[start] == '?')
		return (ft_strdup("?"));
	if (ft_isalpha(input[start]) == 0 \
	&& input[start] != '_' && input[start] != '?')
		return (ft_substr(input, start, 1));
	while (ft_is_sep(input[start + i]) == false && input[start + i] != '$')
		i++;
	return (ft_substr(input, start, i));
}

static void	ft_analyze_expansion(char **input, t_minishell *shell, int i)
{
	t_var	*var;
	char	*var_value;
	char	*var_name;
	bool	should_free;

	should_free = false;
	var_value = "";
	var_name = ft_get_name((*input), i + 1);
	if (var_name == NULL)
		return ;
	var = ft_find_envvar(shell->envvars, var_name);
	if (var)
	{
		var_value = ft_strdup(var->value);
		should_free = true;
	}
	(*input) = ft_strreplace((*input), i, var_value, var_name);
	if (should_free)
	{
		free(var_value);
		should_free = false;
	}
}

void	expand_dolar(char **input, t_minishell *shell)
{
	int		i;

	i = -1;
	while ((*input)[++i])
	{
		if ((*input)[i] == '$' && ft_is_inside_quotes((*input), i) != 1
			&& (*input)[i + 1] != '\0')
		{
			ft_analyze_expansion(input, shell, i);
		}
	}
}
