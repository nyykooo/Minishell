/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   left_trunc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncampbel <ncampbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 16:57:21 by ncampbel          #+#    #+#             */
/*   Updated: 2024/06/20 11:38:58 by ncampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../libs/headers.h"

void	check_left_trunc(char **tokens, t_minishell *shell)
{
	int i;
	int	j;

	i = -1;
	j = 0;
	while (tokens[++i])
	{
		j = -1;
		while(tokens[i][++j] != '\0' && tokens[i][j] != N_LRED)
			if (tokens[i][j] == N_DQUOTE || tokens[i][j] == N_SQUOTE)
				j = skip_nquotes(tokens[i], &j);
		if (tokens[i][j] == N_LRED)
			tokens = ft_array_insert_extra(tokens, tokens[i] + j + 1, "<", i);
		if (!tokens)
		{
			// free_array(tokens);
			printf("Error: failed to insert pipe %s\n", shell->input);
			exit (1);
		}
	}
}
