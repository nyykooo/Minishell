/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pipe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncampbel <ncampbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 16:57:21 by ncampbel          #+#    #+#             */
/*   Updated: 2024/06/13 20:42:20 by ncampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../libs/headers.h"

void	check_pipe(char **tokens, t_minishell *shell)
{
	int i;
	int	j;

	i = -1;
	j = 0;
	while (tokens[++i])
	{
		j = -1;
		while(tokens[i][++j] != '\0' && tokens[i][j] != N_PIPE)
			if (tokens[i][j] == N_DQUOTE || tokens[i][j] == N_SQUOTE)
				j = skip_quotes(tokens[i], &j);
		if (tokens[i][j] == N_PIPE)
			tokens = ft_array_insert_extra(tokens, tokens[i] + j + 1, "|", i);
	}
}