/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namenega <namenega@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/17 13:44:49 by namenega          #+#    #+#             */
/*   Updated: 2021/09/07 16:32:27 by namenega         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

// void	cmd(char *line)
// {
// 	echo(line);
// }

// char	**ms_splitline(char *line)
// {
// 	char	*s;
// 	char	**split_line;

// 	s = ft_strtrim(line, " \t\r\f\v");
// 	split_line = ft_split(s, ' ');
// 	if (!split_line)
// 		return NULL;
// 	return (split_line);
// }

void	ms_loop(void)
{
	char	*line;
	int		status;
	t_token	tok;
	t_lsttok	*tmp;

	status = 1;
	while (status)
	{
		line = readline("splinter_shell> ");
		if (line && *line)
			add_history(line);
		// tokens = ms_splitline(line);
		if (line)
			tok.lsttok = tok_recon(line);
		tmp = tok.lsttok;
		//	cmd(line);
		// status = ms_execute(tokens);
		free(line);
		// free(tok.lsttok);
		while (tok.lsttok)
		{
			tmp = tok.lsttok;
			tok.lsttok = tok.lsttok->next;
			free(tmp);
		}
		//! Need to free lsttok
		
		// free(tokens);
		// status = 0;
	}
}

int	main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	(void)envp;
	if (ac == 1)
		ms_loop();
	else
		printf("Error: Run ./minishell without any other argument\n");
	// system("leaks minishell");
	// exit(0);
	return (0);
}