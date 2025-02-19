/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_child.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarzila <abarzila@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 16:12:23 by abarzila          #+#    #+#             */
/*   Updated: 2025/02/19 11:56:31 by abarzila         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/pipex.h"

void	manage_cmd_first(int *pipe_fd, char **arg, char **env)
{
	char	*path_cmd;
	int		i;

	close(pipe_fd[0]);
	//ouvrir le premier fichier av[1]
	if (open(arg[1], O_APPEND) == -1) // READ_ONLY ??
	{
		perror(errno);
		exit(EXIT_FAILURE);
	}
	//verifier que la commande existe et la recuperer dans le bon path
	path_cmd = find_real_cmd(arg, env);
	if (!path_cmd)
	{
		close(arg[1]);
		perror(errno);
		exit(EXIT_FAILURE);
	}
	//executer la commande arg[1] sur le fichier arg[0]
	execve(path_cmd, arg[2], env);
    perror("execve failed");
	//envoyer ce resultat dans le pipe (cf dup2)
}
