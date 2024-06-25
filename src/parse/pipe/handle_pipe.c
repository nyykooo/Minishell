/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pipe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncampbel <ncampbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 16:57:21 by ncampbel          #+#    #+#             */
/*   Updated: 2024/06/25 16:48:54 by ncampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../libs/headers.h"

char	**check_pipe(char **tokens, t_minishell *shell)
{
	int		i;
	int		j;
	char	**new_tokens;

	i = -1;
	new_tokens = NULL;
	while (tokens[++i] != NULL)
	{
		j = 0;
		printf("tokens[%d]: %s\n", i, tokens[i]);
		while (tokens[i][j] != '\0' && tokens[i][j] != PIPE)
		{
			if (tokens[i][j] == N_DQUOTE || tokens[i][j] == N_SQUOTE)
				j = skip_nquotes(tokens[i], &j);
			j++;
		}
		if (tokens[i][j] == PIPE && (j != 0 && tokens[i][j + 1] != '\0'))
		{
			new_tokens = ft_array_insert_extra(tokens, tokens[i] + j + 1, "|", i);
			if (!new_tokens)
			{
				// free_array(tokens);
				printf("Error: failed to insert pipe %s\n", shell->input);
				exit (1);
			}
			printf("pipe found\n");
			check_pipe(new_tokens, shell);		
			return (new_tokens);
		}
	}
	return (tokens);
}
