/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_child.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarzila <abarzila@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 16:12:23 by abarzila          #+#    #+#             */
/*   Updated: 2025/02/20 16:05:18 by abarzila         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/pipex.h"

void	manage_cmd_first(int *pipe_fd, char **arg, char **env)
{
	char	**cmd_and_flags;
	char	*path_cmd;
	int		fd;

	close(pipe_fd[0]);
	//ouvrir le premier fichier av[1]
	fd = open(arg[1], O_RDWR);
	if (fd == -1)
	{
		perror("(first child) open failed");
		write(pipe_fd[1], "ERROR", 5);
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		exit(EXIT_FAILURE);
	}
	//verifier que la commande existe et la recuperer dans le bon path
	cmd_and_flags = ft_split(arg[2], ' '); //strings de la comd et strings des flags
	path_cmd = find_real_cmd(env, cmd_and_flags);
	printf("(first child) %s\n", path_cmd);
	if (!path_cmd)
	{
		close(fd);
		perror("(first child) command failed");
		write(pipe_fd[1], "ERROR", 5);
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		exit(EXIT_FAILURE);
	}
	//executer la commande arg[1] sur le fichier arg[0] le resultat part dan le pipe
	if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
	{
		perror("dup pid_1");
		write(pipe_fd[1], "ERROR", 5);
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		exit(EXIT_FAILURE);
	}
	execve(path_cmd, cmd_and_flags, env); //arg[2] est censé etre ["ls" "-l"]
    perror("(first child) execve failed");
}
