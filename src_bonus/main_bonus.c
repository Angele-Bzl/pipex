/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarzila <abarzila@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 08:48:06 by abarzila          #+#    #+#             */
/*   Updated: 2025/03/18 11:24:09 by abarzila         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header_bonus/pipex_bonus.h"
#include <fcntl.h>
#include <stdio.h>

static void	manage_child(char *cmd, char **env, pid_t *pid)
{
	char	**cmd_and_flags;
	char	*path_cmd;

	if (ft_strlen(cmd) == 0)
		putendl_exit("permission denied", 127, pid);
	cmd_and_flags = ft_split(cmd, ' ');
	if (!cmd_and_flags)
		putendl_exit("malloc failed", 127, pid);
	path_cmd = find_real_cmd(env, cmd_and_flags);
	if (!path_cmd)
	{
		free_tab(cmd_and_flags);
		putendl_exit("command failed", 127, pid);
	}
	if (execve(path_cmd, cmd_and_flags, env) == -1)
	{
		free(path_cmd);
		free_tab(cmd_and_flags);
		putendl_exit("execution failed", 127, pid);
	}
}

static void	manage_first_cmd(int *pipe_fd, t_user_env user_env, pid_t *pid)
{
	int	infile;

	if (pipe(pipe_fd) == -1)
		close_perror_exit(0, 0, "pipe", pid);
	pid[0] = fork();
	if (pid[0] == -1)
		close_perror_exit(pipe_fd, 0, "fork", pid);
	if (pid[0] == 0)
	{
		infile = open(user_env.av[1], O_RDONLY);
		if (infile == -1)
			close_perror_exit(pipe_fd, 0, "open", pid);
		if (dup2(infile, STDIN_FILENO) == -1)
			close_perror_exit(pipe_fd, infile, "dup2", pid);
		if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
			close_perror_exit(pipe_fd, infile, "dup2", pid);
		close(infile);
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		manage_child(user_env.av[2], user_env.env, pid);
	}
}

static void	manage_middle_cmds(int *pipe_fd, t_user_env user_env, pid_t *pid)
{
	int	i;
	int	previous_output;

	i = 1;
	while (i < user_env.ac - 4)
	{
		close(pipe_fd[1]);
		previous_output = pipe_fd[0];
		if (pipe(pipe_fd) == -1)
			close_perror_exit(0, 0, "pipe", pid);
		pid[i] = fork();
		if (pid[i] == -1)
			close_perror_exit(pipe_fd, 0, "fork", pid);
		if (pid[i] == 0)
		{
			if (dup2(previous_output, STDIN_FILENO) == -1)
				close_perror_exit(pipe_fd, previous_output, "dup2", pid);
			if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
				close_perror_exit(pipe_fd, previous_output, "dup2", pid);
			close_all(pipe_fd, previous_output);
			manage_child(user_env.av[i + 2], user_env.env, pid);
		}
		close(previous_output);
		i++;
	}
}

static void	manage_last_cmd(int *pipe_fd, t_user_env env, pid_t *pid)
{
	int	outfile;

	pid[env.ac - 4] = fork();
	if (pid[env.ac - 4] == -1)
		close_perror_exit(pipe_fd, 0, "fork", pid);
	if (pid[env.ac - 4] == 0)
	{
		outfile = open(env.av[env.ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (outfile == -1)
			close_perror_exit(pipe_fd, 0, "open", pid);
		if (dup2(pipe_fd[0], STDIN_FILENO) == -1)
			close_perror_exit(pipe_fd, outfile, "dup2", pid);
		if (dup2(outfile, STDOUT_FILENO) == -1)
			close_perror_exit(pipe_fd, outfile, "dup2", pid);
		close_all(pipe_fd, outfile);
		manage_child(env.av[env.ac - 2], env.env, pid);
	}
}

int	main(int ac, char **av, char **env)
{
	int			pipe_fd[2];
	pid_t		*pid;
	int			exit_status;
	t_user_env	user_env;

	if (check_env_av(ac, env) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	pid = malloc(sizeof (pid_t) * (ac - 3));
	if (!pid)
	{
		ft_putendl_fd("Error\nMalloc failed", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	init_struct_env(&user_env, ac, av, env);
	manage_first_cmd(pipe_fd, user_env, pid);
	if (ac > 5)
		manage_middle_cmds(pipe_fd, user_env, pid);
	manage_last_cmd(pipe_fd, user_env, pid);
	close_all(pipe_fd, 0);
	exit_status = wait_for_pid(pid, ac);
	free(pid);
	return (exit_status);
}
