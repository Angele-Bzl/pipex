/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarzila <abarzila@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 14:45:07 by abarzila          #+#    #+#             */
/*   Updated: 2025/02/18 11:13:02 by abarzila         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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
	int	pipe_fd[2];
	pid_t	pid;
	char **arguments;
	int	i;

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
	arguments = malloc(sizeof(char*) * ac - 1);
	i = 0;
	while (i < ac - 1)
	{
		arguments[i] = ft_strdup(av[i + 1]);
		i++;
	}
	if (pid == 0)
	{
		process_is_child(pipe_fd, arguments, env);
	}
	else
	{
		process_is_parent(pipe_fd, arguments, env);
	}
	return (0);
}
