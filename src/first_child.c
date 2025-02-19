/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_child.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarzila <abarzila@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 16:12:23 by abarzila          #+#    #+#             */
/*   Updated: 2025/02/19 16:04:38 by abarzila         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/pipex.h"

void	manage_cmd_first(int *pipe_fd, char **arg, char **env)
{
	char	*path_cmd;
	int		fd;

	close(pipe_fd[0]);
	//ouvrir le premier fichier av[1]
	fd = open(arg[1], O_APPEND);
	if (fd == -1) // READ_ONLY ??
	{
		perror("open failed");
		exit(EXIT_FAILURE);
	}
	//verifier que la commande existe et la recuperer dans le bon path
	path_cmd = find_real_cmd(arg[2], env);
	if (!path_cmd)
	{
		close(fd);
		perror("command failed");
		exit(EXIT_FAILURE);
	}
	//executer la commande arg[1] sur le fichier arg[0] le resultat part dan le pipe
	execve(path_cmd, &arg[2], env);
    perror("execve failed");
}
