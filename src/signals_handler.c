/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunhenr <brunhenr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 10:47:51 by brunhenr          #+#    #+#             */
/*   Updated: 2024/06/08 10:47:55 by brunhenr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <termios.h>
#include "../libs/headers.h"

struct termios original_termios, new_termios, check_termios;

void	edit_termios(void)
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
}

