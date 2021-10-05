/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namenega <namenega@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 16:02:42 by namenega          #+#    #+#             */
/*   Updated: 2021/10/05 17:16:01 by namenega         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include <stdio.h>

/*
** Global for Signals
*/

pid_t	g_sig = 0;

void	handle_sigint(int sig)
{
	// (void)sig;
	// printf("\033[32m Handling CTRL-C\033[0m\n");
	printf("\n");
	if (sig == SIGINT && g_sig == 0)
	{
		rl_on_new_line();			// Regenerate the prompt on a newline
		// if (*rl_line_buffer)			// Buffer empty
			// TODO:set RET to 130
		rl_replace_line("", 0);		// Clear the previous text
		rl_redisplay();				// Display the new buffer
	}
	else if (sig == SIGINT && g_sig != 0)
	{
		kill(g_sig, SIGCONT);
		// write(STDOUT_FILENO, "\n", 1);
	}
}

void	signal_handling(void)
{
	signal(SIGINT, handle_sigint);	//CTRL+C
	signal(SIGQUIT, SIG_IGN);		// Ignore SIGQUIT aka cmd+backslash
}