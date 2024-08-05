/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncampbel <ncampbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 22:31:53 by ncampbel          #+#    #+#             */
/*   Updated: 2024/08/05 22:32:42 by ncampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../libs/headers.h"

static bool	ft_check_separator(char c)
{
	if (c == '\"' || c == '\\' || c == '$' || c == '`')
		return (true);
	return (false);
}

static char	*ft_prepare_value(char *content)
{
	char	*value;
	int		i;
	int		j;
	int		count_meta;

	i = -1;
	count_meta = 0;
	while (content[++i] != '\0')
	{
		if (ft_check_separator(content[i]))
			count_meta++;
	}
	value = malloc(sizeof(char) * (ft_strlen(content) + count_meta + 1));
	if (value == NULL)
		return (NULL);
	i = -1;
	j = 0;
	while (content[++i] != '\0')
	{
		if (ft_check_separator(content[i]))
			value[j++] = '\\';
		value[j++] = content[i];
	}
	value[j] = '\0';
	return (value);
}

void	ft_print_export(t_var *current)
{
	char	*value;

	value = NULL;
	if (current->exp == true && current->env == true && \
		current->value != NULL)
	{
		value = ft_prepare_value(current->value);
		printf("declare -x %s=\"%s\"\n", current->name, value);
	}
	else if (current->exp == true && current->value)
	{
		value = ft_prepare_value(current->value);
		printf("declare -x %s=\"%s\"\n", current->name, value);
	}
	else if (current->exp == true && current->value == NULL)
		printf("declare -x %s\n", current->name);
	if (value)
		free(value);
}
