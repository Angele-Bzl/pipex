/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarzila <abarzila@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 16:12:23 by abarzila          #+#    #+#             */
/*   Updated: 2025/02/18 13:43:23 by abarzila         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	process_is_parent(int *pipe_fd, char **arg, char **env)
{
	char	*path_cmd;
	int	i;

	close(pipe_fd[0]);
	//ouvrir le premier fichier av[1]
	if (access(arg[0], F_OK) || open(arg[0], O_APPEND) == -1)
	{
		perror(errno);
		exit(EXIT_FAILURE);
	}
	//verifier que la commande existe et la recuperer dans le bon path
	path_cmd = real_cmd(arg, env);
	if (!path_cmd)
	{
		close(arg[0]);
		perror(errno);
		exit(EXIT_FAILURE);
	}
	//verifier qu'on a les droits sur le fichier
	if (access(arg[0], R_OK)) /*the access asked depends on the command????????*/
	{
		close(arg[0]);
		free(path_cmd);
		perror(errno);
		exit(EXIT_FAILURE);
	}
	//executer la commande arg[1] sur le fichier arg[0]
	/*COMMENT FAIRE POUR EXECUTER AVEC LES FLAGS ?*/
	dup2(1, pipe_fd[1]);
	if (execve(path_cmd, arg[0], env) == -1)
	{
        perror("execve failed");
    }
	//envoyer ce resultat dans le pipe (cf dup2)
}
