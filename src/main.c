/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarzila <abarzila@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 14:45:07 by abarzila          #+#    #+#             */
/*   Updated: 2025/02/19 11:55:29 by abarzila         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/pipex.h"

/*
1	initialiser le pipe
2	checker les arg
ouvrir les fichiers (gere here_doc et /dev/random)
get_next_line quoi
3	parser la commande
trouve le chemin de la commande avec l'environnement
recuperer l'argument pour pour cette commande
4	parser les arg (c'est quoi la dif avec check ?)
5	executer les commandes
6	tout nettoyer
*/

int	main(int ac, char **av, char **env)
{
	int		pipe_fd[2];
	pid_t	pid;
	int		i;

	if (ac != 4)
		return (1);
    if (pipe(pipe_fd) == -1)
	{
		perror("pipe");
        exit(EXIT_FAILURE);
    }

    pid = fork();
    if (pid == -1)
	{
		perror("fork");
        exit(EXIT_FAILURE);
    }
	if (pid == 0)
	{
		if (dup2(1, pipe_fd[1]) == -1)
		{
			/*fail*/
		}
		manage_cmd_first(pipe_fd, av, env);
	}
	else
	{
		/*gerer deux trois trucs dans le parent avant de refaire un enfant avec fork*/
		pid = fork();
		if (pid == -1)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		if (pid == 0)
		{
			if (dup2(1, av[3]) == -1)
			{
				/*fail*/
			}
			manage_cmd_last(pipe_fd, av, env);
		}
		else
		{

		}
	}
	return (0);
}
