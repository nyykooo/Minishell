/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   right_apend.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncampbel <ncampbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 00:37:03 by ncampbel          #+#    #+#             */
/*   Updated: 2024/06/16 20:25:05 by ncampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "../../../libs/headers.h"

void	check_right_apend(char **tokens, t_minishell *shell)
{
	int i;
	int	j;

	i = -1;
	j = 0;
	while (tokens[++i])
	{
		j = -1;
		while(tokens[i][++j] != '\0' && tokens[i][j] != N_RRED)
		{
			if (tokens[i][j] == N_DQUOTE || tokens[i][j] == N_SQUOTE)
				j = skip_quotes(tokens[i], &j);
			if (tokens[i][j] == N_RRED && tokens[i][j + 1] == N_RRED)
				tokens = ft_array_insert_extra(tokens, tokens[i] + j + 1, ">>", i);
			if (!tokens)
			{
				// free_array(tokens);
				printf("Error: failed to insert pipe %s\n", shell->input);
				exit (1);
			}
		}
	}
}
