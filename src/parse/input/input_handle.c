/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_handle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncampbel <ncampbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 13:37:26 by ncampbel          #+#    #+#             */
/*   Updated: 2024/08/15 12:20:48 by ncampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../libs/headers.h"

static bool	space_trim(char *input, char *temp)
{
	static int	i = 0;
	static int	j = 0;
	char		c;

	if (!input[i])
		return (false);
	while (input[i] && input[i] != '\'' \
	&& input[i] != '\"' && !ft_isspace(input[i]))
		temp[j++] = input[i++];
	if (input[i] == '\'' || input[i] == '\"')
	{
		c = input[i];
		temp[j++] = input[i++];
		while (input[i] && input[i] != c)
			temp[j++] = input[i++];
		temp[j++] = input[i++];
	}
	if (input[i] && ft_isspace(input[i]))
		temp[j++] = ' ';
	while (input[i] && ft_isspace(input[i]))
		i++;
	temp[j] = '\0';
	if (input[i] == '\0')
		return (i = 0, j = 0, true);
	return (false);
}

static char	*trim_hub(char *input)
{
	char	*temp;

	temp = ft_calloc(ft_strlen(input) + 1, sizeof(char));
	if (!temp)
		return (NULL);
	while (space_trim(input, temp) == false)
		(void)0;
	return (temp);
}

static int	quote_check(const char *input)
{
	char	c;

	c = 0;
	while (*input != '\0')
	{
		if (*input == '"' || *input == '\'')
		{
			if (c == 0)
				c = *input;
			else if (c == *input)
				c = 0;
		}
		input++;
	}
	return ((c == '\'') + ((c == '\"') * 2));
}

static int	input_cleaner(char *input)
{
	char	*trim;

	if (!input)
		return (-1);
	trim = trim_hub(input);
	if (!trim)
		return (-1);
	ft_strlcpy(input, trim, ft_strlen(trim) + 1);
	free(trim);
	return (0);
}

bool	ft_input_manager(t_minishell *shell)
{
	if (quote_check(shell->input))
	{
		ft_print_error(false, 0, 1, "-minishell: unmatched quote\n");
		return (false);
	}
	if (input_cleaner(shell->input) == -1)
	{
		ft_print_error(true, 2, 1, "-minishell: failed to allocate memory\n");
	}
	return (true);
}
