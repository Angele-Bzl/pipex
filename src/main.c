/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarzila <abarzila@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 14:45:07 by abarzila          #+#    #+#             */
/*   Updated: 2025/02/21 11:35:48 by abarzila         ###   ########.fr       */
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
	pid_t	pid_1;
	pid_t	pid_2;

	if (ac != 5)
	{
		ft_putendl_fd("Error\nInvalid number of argument", STDERR_FILENO);
		return(EXIT_FAILURE);
	}
	//
	if (pipe(pipe_fd) == -1)
	{
		perror("pipe");
		return(EXIT_FAILURE);
	}
	pid_1 = fork();
	if (pid_1 == -1)
	{
		perror("fork pid_1");
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		return(EXIT_FAILURE);
	}
	if (pid_1 == 0)
	{
		manage_cmd_first(pipe_fd, av, env);
	}
	close(pipe_fd[1]);
	
	close(pipe_fd[1]);

	//
	waitpid(pid_1, 0, 0);
	pid_2 = fork();
	if (pid_2 == -1)
	{
		perror("fork pid_2");
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		return(EXIT_FAILURE);
	}
	if (pid_2 == 0)
	{
		manage_cmd_last(pipe_fd, av, env);
	}
	waitpid(pid_2, 0, 0);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	return (0);
}
