/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarzila <abarzila@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 08:48:06 by abarzila          #+#    #+#             */
/*   Updated: 2025/03/13 12:16:34 by abarzila         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header_bonus/pipex_bonus.h"
#include <fcntl.h>
#include <stdio.h>
#include <sys/wait.h>

static void	manage_child(char *cmd, char **env)
{
	char	**cmd_and_flags;
	char	*path_cmd;

	if (ft_strlen(cmd) == 0)
		putendl_exit("permission denied", 127);
	cmd_and_flags = ft_split(cmd, ' ');
	if (!cmd_and_flags)
		putendl_exit("malloc failed", 127);
	path_cmd = find_real_cmd(env, cmd_and_flags);
	if (!path_cmd)
	{
		free_tab(cmd_and_flags);
		putendl_exit("command failed", 127);
	}
	if (execve(path_cmd, cmd_and_flags, env) == -1)
	{
		free(path_cmd);
		free_tab(cmd_and_flags);
		putendl_exit("execution failed", 127);
	}
}

static void	manage_first_cmd(int *pipe_fd, t_user_env user_env, pid_t *pid)
{
	int	infile;

	if (pipe(pipe_fd) == -1)
		close_perror_exit(0, 0, "pipe", EXIT_FAILURE);
	pid[0] = fork();
	if (pid[0] == -1)
		close_perror_exit(pipe_fd, 0, "fork", EXIT_FAILURE);
	if (pid[0] == 0)
	{
		infile = open(user_env.av[1], O_RDONLY);
		if (infile == -1)
			close_perror_exit(pipe_fd, 0, "open", EXIT_FAILURE);
		if (dup2(infile, STDIN_FILENO) == -1)
			close_perror_exit(pipe_fd, infile, "dup2", EXIT_FAILURE);
		if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
			close_perror_exit(pipe_fd, infile, "dup2", EXIT_FAILURE);
		close(infile);
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		manage_child(user_env.av[2], user_env.env);
	}
}

static void	manage_middle_cmds(int *pipe_fd, t_user_env user_env, pid_t *pid)
{
	int	i;
	int	previous_pipe_output;

	previous_pipe_output = pipe_fd[0];
	if (pipe(pipe_fd) == -1)
		close_perror_exit(0, 0, "pipe", EXIT_FAILURE);
	i = 1;
	while (i < user_env.ac - 4)
	{
		pid[i] = fork();
		if (pid[i] == -1)
			close_perror_exit(pipe_fd, 0, "fork", EXIT_FAILURE);

		if (pid[i] == 0)
		{
			if (dup2(previous_pipe_output, STDIN_FILENO) == -1)
				close_perror_exit(pipe_fd, previous_pipe_output, "dup2", EXIT_FAILURE);
			if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
				close_perror_exit(pipe_fd, previous_pipe_output, "dup2", EXIT_FAILURE);
			close(previous_pipe_output);
			close(pipe_fd[0]);
			close(pipe_fd[1]);
			manage_child(user_env.av[2], user_env.env);
		}
		i++;
	}
}

static void	manage_last_cmd(int *pipe_fd, t_user_env user_env, pid_t *pid)
{
	int	outfile;

	pid[user_env.ac - 4] = fork();
	if (pid[user_env.ac - 4] == -1)
		close_perror_exit(pipe_fd, 0, "fork", EXIT_FAILURE);
	if (pid[user_env.ac - 4] == 0)
	{
		outfile = open(user_env.av[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (outfile == -1)
			close_perror_exit(pipe_fd, 0, "open", EXIT_FAILURE);
		if (dup2(pipe_fd[0], STDIN_FILENO) == -1)
			close_perror_exit(pipe_fd, outfile, "dup2", EXIT_FAILURE);
		if (dup2(outfile, STDOUT_FILENO) == -1)
			close_perror_exit(pipe_fd, outfile, "dup2", EXIT_FAILURE);
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		close(outfile);
		manage_child(user_env.av[3], user_env.env);
	}
}

static int	wait_for_pid(pid_t *pid)
{
	int	i;
	int	status;

	i = 0;
	while (i < 2) //number of cmd/children
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

int	main(int ac, char **av, char **env)
{
	int		pipe_fd[2];
	pid_t	*pid;
	int		exit_status;
	t_user_env	user_env;

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
	pid = malloc(sizeof (pid_t) * (ac - 3));
	user_env.ac = ac;
	user_env.av = av;
	user_env.env = env;
	manage_first_cmd(pipe_fd, user_env, pid);
	manage_middle_cmds(pipe_fd, user_env, pid);
	manage_last_cmd(pipe_fd, user_env, pid);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	exit_status = wait_for_pid(pid);
	exit(exit_status);
}
