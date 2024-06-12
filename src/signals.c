/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunhenr <brunhenr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 17:00:04 by brunhenr          #+#    #+#             */
/*   Updated: 2024/06/12 17:14:47 by brunhenr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libs/headers.h"
#include <termios.h>

struct termios original_termios, new_termios, check_termios;

void	handle_sigint(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

/*void	edit_termios(void)
{
	if (tcgetattr(STDIN_FILENO, &original_termios) == -1)
		perror("tcgetattr");
	new_termios = original_termios;
	new_termios.c_lflag &= ~ISIG;
	if (tcsetattr(STDIN_FILENO, TCSANOW, &new_termios) == -1)
		perror("tcsetattr");
	if (tcgetattr(STDIN_FILENO, &check_termios) == -1)
        perror("tcgetattr to check");
    if (check_termios.c_lflag & ISIG)
        printf("ISIG is still enabled\n");
    else
        printf("ISIG is disabled\n");
}*/