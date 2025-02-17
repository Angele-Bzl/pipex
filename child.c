/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarzila <abarzila@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 16:04:01 by abarzila          #+#    #+#             */
/*   Updated: 2025/02/13 16:19:25 by abarzila         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	process_is_child(int *pipe_fd)
{
	char	buf;

	close(pipe_fd[1]);
	while (read(pipe_fd[0], &buf, 1))
	{

	}
	//lire le resultat envoyé par pipe_fd[1]
	//ouvrir le fichier av[4]
	//executer la commande av[3] et stocker son resultat dans le fichier av[4]
}
