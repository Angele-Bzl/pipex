/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils01_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarzila <abarzila@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 08:56:39 by abarzila          #+#    #+#             */
/*   Updated: 2025/03/18 11:23:01 by abarzila         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header_bonus/pipex_bonus.h"
#include <stdio.h>

void	close_all(int *pipe_fd, int file)
{
	if (file)
		close(file);
	if (pipe_fd && pipe_fd[0])
		close(pipe_fd[0]);
	if (pipe_fd && pipe_fd[1])
		close(pipe_fd[1]);
}

void	init_struct_env(t_user_env *user_env, int ac, char **av, char **env)
{
	user_env->ac = ac;
	user_env->av = av;
	user_env->env = env;
}

int	wait_for_pid(pid_t *pid, int ac)
{
	int	i;
	int	status;

	i = 0;
	while (i < (ac - 3))
	{
		if (waitpid(pid[i], &status, 0) == -1)
		{
			perror("wait");
			exit(EXIT_FAILURE);
		}
		i++;
	}
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (EXIT_SUCCESS);
}

int	check_env_av(int ac, char **env)
{
	if (ac < 5)
	{
		ft_putendl_fd("Error\nInvalid number of argument", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	if (!env || !env[0])
	{
		ft_putendl_fd("Error\nNo environment", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
