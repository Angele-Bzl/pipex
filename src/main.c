/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarzila <abarzila@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 14:45:07 by abarzila          #+#    #+#             */
/*   Updated: 2025/03/03 16:38:31 by abarzila         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/pipex.h"

/*
TO DO

- les cmd qui utilisent le infile ne s'execute pas (grep, cat)
- revoir la hierarchie des fonctions entre les parents et les enfants
- gerer les cas particuliers (chemins cachés, cmd créées manuellement)
- anticiper les cas d'erreur (cmd invalide, fail de write...)
- gerer une exit propre en cas d'erreur
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
	//

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
	waitpid(pid_1, 0, 0);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	return (0);
}
