/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarzila <abarzila@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 14:45:07 by abarzila          #+#    #+#             */
/*   Updated: 2025/02/19 17:11:31 by abarzila         ###   ########.fr       */
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
	int		fd;
	pid_t	pid;

	if (ac != 5)
	return (1);
	// printf("hello\n");
    if (pipe(pipe_fd) == -1)
	{
		printf("00\n");
		perror("pipe");
        exit(EXIT_FAILURE);
    }
    pid = fork();
    if (pid == -1)
	{
		printf("01\n");
		perror("fork");
        exit(EXIT_FAILURE);
    }
	if (pid == 0)
	{
		printf("02\n");
		if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
		{
			/*fail*/
		}
		manage_cmd_first(pipe_fd, av, env);
	}
	else
	{
		wait;
		printf("03\n");
		pid = fork();
		if (pid == -1)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		if (pid == 0)
		{
			fd = open(av[4], O_APPEND);
			if (fd == -1)
			{
				/*fail*/
			}
			if (dup2(fd, STDOUT_FILENO) == -1)
			{
				/*fail*/
			}
			manage_cmd_last(pipe_fd, av, env);
		}
		else
		{
			wait;
			/*tout nettoyer*/
		}
	}
	return (0);
}
