/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarzila <abarzila@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 14:45:07 by abarzila          #+#    #+#             */
/*   Updated: 2025/03/05 09:28:01 by abarzila         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/pipex.h"

int	main(int ac, char **av, char **env)
{
	int		pipe_fd[2];
	pid_t	pid_1;
	pid_t	pid_2;

	if (ac != 5)
	{
		ft_putendl_fd("Error\nInvalid number of argument", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	if (pipe(pipe_fd) == -1)
		close_fd_and_pipe_and_exit(0, NULL, "pipe", 1);
	pid_1 = fork();
	if (pid_1 == -1)
		close_fd_and_pipe_and_exit(0, pipe_fd, "fork 01", 1);
	if (pid_1 == 0)
		manage_cmd_first(pipe_fd, av, env);
	close(pipe_fd[1]);
	pid_2 = fork();
	if (pid_2 == -1)
		close_fd_and_pipe_and_exit(0, pipe_fd, "fork 02", 1);
	if (pid_2 == 0)
		manage_cmd_last(pipe_fd, av, env);
	waitpid(pid_1, 0, 0);
	close_fd_and_pipe_and_exit(0, pipe_fd, NULL, 0);
}
