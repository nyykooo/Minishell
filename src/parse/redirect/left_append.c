/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   left_append.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncampbel <ncampbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 00:37:03 by ncampbel          #+#    #+#             */
/*   Updated: 2024/06/25 15:38:31 by ncampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "../../../libs/headers.h"

char	**check_left_apend(char **tokens, t_minishell *shell)
{
	int i;
	int	j;
	char **new_tokens;

	i = -1;
	j = 0;
	new_tokens = NULL; 
	while (tokens[++i])
	{
		j = -1;
		while(tokens[i][++j] != '\0' && tokens[i][j] != LRED)
		{
			if (tokens[i][j] == N_DQUOTE || tokens[i][j] == N_SQUOTE)
				j = skip_nquotes(tokens[i], &j);
			if (tokens[i][j] == LRED && tokens[i][j + 1] == LRED) // blindar para mais de 3 seguidos
			{
					new_tokens = ft_array_insert_extra(tokens, tokens[i] + j + 1, "<<", i);
				if (!new_tokens)
				{
					// free_array(tokens);
					printf("Error: failed to insert pipe %s\n", shell->input);
					exit (1);
				}
				return (new_tokens);
			}
		}
	}
	return (tokens);
}
