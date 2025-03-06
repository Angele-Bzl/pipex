/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarzila <abarzila@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 14:45:07 by abarzila          #+#    #+#             */
/*   Updated: 2025/03/06 14:30:47 by abarzila         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/pipex.h"

static int	start_wait(pid_t pid_1, pid_t pid_2, int *pipe_fd)
{
	int	status;

	if (waitpid(pid_1, &status, 0) == -1)
		close_all_exit(0, pipe_fd, "wait", EXIT_FAILURE);
	if (waitpid(pid_2, &status, 0) == -1)
		close_all_exit(0, pipe_fd, "wait", EXIT_FAILURE);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (EXIT_SUCCESS);
}

int	main(int ac, char **av, char **env)
{
	int		pipe_fd[2];
	pid_t	pid_1;
	pid_t	pid_2;
	int		exit_status;

	if (ac != 5)
	{
		ft_putendl_fd("Error\nInvalid number of argument", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	if (pipe(pipe_fd) == -1)
		close_all_exit(0, NULL, "pipe", EXIT_FAILURE);
	pid_1 = fork();
	if (pid_1 == -1)
		close_all_exit(0, pipe_fd, "fork", EXIT_FAILURE);
	if (pid_1 == 0)
		manage_cmd_first(pipe_fd, av, env);
	close(pipe_fd[1]);
	pid_2 = fork();
	if (pid_2 == -1)
		close_all_exit(0, pipe_fd, "fork", EXIT_FAILURE);
	if (pid_2 == 0)
		manage_cmd_last(pipe_fd, av, env);
	exit_status = start_wait(pid_1, pid_2, pipe_fd);
	close(0);
	close(1);
	close(2);
	close_all_exit(0, pipe_fd, NULL, exit_status);
}
