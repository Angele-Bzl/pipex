/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarzila <abarzila@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 16:12:23 by abarzila          #+#    #+#             */
/*   Updated: 2025/02/14 14:58:28 by abarzila         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	process_is_parent(int *pipe_fd, char **arg)
{
	close(pipe_fd[0]);
	//ouvrir le premier fichier av[1]
	if (open(arg[0], O_APPEND) == -1)
	{
		perror(errno);
		exit(EXIT_FAILURE);
	}
	//verifier que la commande existe
	//verifier qu'on a les droits sur le fichier
	//executer la commande arg[1] sur le fichier arg[0]
	if (execve(arg[0], arg, NULL) == -1)
	{
        perror("execve failed");
    }
	//envoyer ce resultat dans le pipe
}
