/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dolar.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncampbel <ncampbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 14:29:05 by ncampbel          #+#    #+#             */
/*   Updated: 2024/07/22 21:20:46 by ncampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libs/headers.h"

static bool	ft_is_sep(char sep)
{
	if (sep == ' ' || sep == '\0' || sep == '"' || sep == '\''
		|| sep == '=' || sep == '/')
		return (true);
	return (false);
}

static char *get_name(char *input, int start)
{
	int	i;
	
	i = 0;
	if (ft_is_sep(input[start]) == true)
		return (NULL);
	if (input[start] == '?')
		return (ft_strdup("?"));
	if (ft_isalpha(input[start]) == 0 && input[start] != '_' && input[start] != '?')
		return (ft_substr(input, start, 1));
	while (ft_is_sep(input[start + i]) == false && input[start + i] != '$')
		i++;
	return (ft_substr(input, start, i));
}

//copy until str/join str and expanded/ and join the rest of the str

static char	*ft_strreplace(char *src, int i, char *insert, char *name)
{
	char	*str_frag;
	char	*tmp;
	char	*new;

	str_frag = ft_substr(src, 0, i);
	tmp = ft_strjoin(str_frag, insert);
	new = ft_strjoin(tmp, src + i + ft_strlen(name) + 1);
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
	bool	squote;

	i = -1;
	var_value = "";
	squote = false;
	while ((*input)[++i])
	{
		if ((*input)[i] == '\'')
			squote = !squote;
		if ((*input)[i] == '~' && squote == false && (*input)[i - 1] == ' ' &&
			((*input)[i + 1] == ' ' || (*input)[i + 1] == '\0'
			|| (*input)[i + 1] == '/'))
		{
			var = find_envvar(shell->envvars, "HOME");
			if (var)
				var_value = ft_strdup(var->value);
			(*input) = ft_strreplace((*input), i, var_value, "~");
		}
	}
}

void	expand_hashtag(char **input)
{
	
	int		i;

	i = -1;
	while ((*input)[++i])
	{
		if ((*input)[i] == '#' && is_inside_quotes((*input), i) == 0)
			(*input)[i] = 0;
	}
}

void	expand_dolar(char **input, t_minishell *shell)
{
	int		i;
	t_var	*var;
	char	*var_value;
	char	*var_name;

	i = -1;
	while ((*input)[++i])
	{
		var_value = "";
		if ((*input)[i] == '$' && is_inside_quotes((*input), i) != 1
			&& (*input)[i + 1] != '\0')
		{
			var_name = get_name((*input), i + 1);
			if (var_name == NULL)
				continue ;
			var = find_envvar(shell->envvars, var_name);
			if (var)
				var_value = ft_strdup(var->value);
			(*input) = ft_strreplace((*input), i, var_value, var_name);
			if (var_name)
				free(var_name);
			if (var_value[0] != '\0')
				free(var_value);
			if ((*input)[i] != '$')
				i--;
		}
	}
}
