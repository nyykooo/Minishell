/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dolar.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncampbel <ncampbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 14:29:05 by ncampbel          #+#    #+#             */
/*   Updated: 2024/07/12 14:53:14 by ncampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libs/headers.h"


static char *get_name(char *input, int start)
{
	int	i;
	
	i = 0;
	if (input[start] == 0)
		return (ft_strdup(""));
	if (ft_isalpha(input[start]) == 0 && input[start] != '_' && input[start] != '?')
		return (ft_substr(input, start, 1));
	while (input[start + i] != '\0' && input[start + i] != ' '
			&& input[start + i] != '"' && input[start + i] != '\''
			&& input[start + i] != '$' && input[start + i] != '='
			&& input[start + i] != '/')
		i++;
	return (ft_substr(input, start, i));
}

static char	*ft_strreplace(char *src, int i, char *insert, int flag)
{
	char	*new;
	int		del_len;
	int		insert_len;
	int		size;
	char	*name;

	if (src[i + 1] == '\0')
		insert = ft_strdup("$");
	insert_len = ft_strlen(insert);
	del_len = 0;
	name = get_name(src, i + 1);
	del_len = ft_strlen(name) + 1;
	if (flag == 1)
		del_len = 1;
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
	free(name);
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
			(*input) = ft_strreplace((*input), i, var_value, 1);
		}
	}
}

void	expand_hashtag(char **input)
{
	
	int		i;
	bool	squote;
	bool	dquote;

	i = -1;
	squote = false;
	dquote = false;
	while ((*input)[++i])
	{
		if ((*input)[i] == '"' && squote == false)
			dquote = !dquote;
		if ((*input)[i] == '\'')
			squote = !squote;
		if ((*input)[i] == '#' && squote == false)
			(*input)[i] = 0;
	}
}

void	expand_dolar(char **input, t_minishell *shell)
{
	int		i;
	t_var	*var;
	char	*var_value;
	char	*var_name;
	bool	squote;
	bool	dquote;

	i = -1;
	squote = false;
	dquote = false;
	while ((*input)[++i])
	{
		var_value = "";
		if ((*input)[i] == '"' && squote == false)
			dquote = !dquote;
		if ((*input)[i] == '\'' && dquote == false)
			squote = !squote;
		if ((*input)[i] == '$' && squote == false)
		{
			var_name = get_name((*input), i + 1);
			var = find_envvar(shell->envvars, var_name);
			if (var)
				var_value = ft_strdup(var->value);
			(*input) = ft_strreplace((*input), i, var_value, 0);
			if (var_name)
				free(var_name);
			if (var_value[0] != '\0')
				free(var_value);
		}
	}
}
