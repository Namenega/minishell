/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namenega <namenega@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 16:02:42 by namenega          #+#    #+#             */
/*   Updated: 2021/10/07 17:46:32 by namenega         ###   ########.fr       */
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
		// if (*rl_line_buffer)			// Buffer empty
			// TODO:set RET to 130
		rl_on_new_line();			// Regenerate the prompt on a newline
		rl_replace_line("", 0);		// Clear the previous text
		rl_redisplay();				// Display the new buffer
		// close(STDIN_FILENO);
		// write(STDOUT_FILENO, "\n", 1);
	}
	else if (sig == SIGINT && g_sig != 0)
	{
		kill(g_sig, SIGCONT);
		// write(STDOUT_FILENO, "\n", 1);
	}
}

void	handle_sigquit(int sig)
{
	if (sig == SIGQUIT && g_sig != 0)
	{
		if (!kill(g_sig, SIGCONT))
			write(STDOUT_FILENO, "Quit: 3\n", 8);
	}
	else if (sig == SIGQUIT && g_sig == 0)
	{
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

// void	handle_sigusr1(int sig)
// {
// 	if (sig == SIGUSR1)
// 	{
// 		close(STDIN_FILENO);
// 		write(STDOUT_FILENO, "exit\n", 1);
// 		exit(EXIT_SUCCESS);
// 	}
// }

void	signal_handling(void)
{
	signal(SIGINT, handle_sigint);	//CTRL+C
	// signal(SIGUSR1, handle_sigusr1);
	signal(SIGQUIT, SIG_IGN);		// Ignore SIGQUIT aka cmd+backslash
}
