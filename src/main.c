/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarzila <abarzila@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 08:48:06 by abarzila          #+#    #+#             */
/*   Updated: 2025/03/11 14:57:21 by abarzila         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/pipex.h"
#include <fcntl.h>
#include <stdio.h>
#include <sys/wait.h>




static int	init_hyp_path(char **hyp_path, char **cmd_and_flags, char **path)
{
	char	*path_w_backslash;
	int		i;

	i = 0;
	while (path[i])
	{
		path_w_backslash = ft_strjoin(path[i], "/");
		if (!path_w_backslash)
		{
			ft_putendl_fd("malloc failed", STDERR_FILENO);
			return (0);
		}
		hyp_path[i] = ft_strjoin(path_w_backslash, cmd_and_flags[0]);
		if (!hyp_path[i])
		{
			ft_putendl_fd("malloc failed", STDERR_FILENO);
			return (0);
		}
		free(path_w_backslash);
		i++;
	}
	return (1);
}

static char	*find_path_cmd(char **hypothetical_path_cmd, char **path)
{
	int		i;
	char	*real_path;

	i = 0;
	real_path = NULL;
	while (path[i])
	{
		if (!access(hypothetical_path_cmd[i], X_OK))
		{
			real_path = ft_strdup(hypothetical_path_cmd[i]);
		}
		free(hypothetical_path_cmd[i]);
		i++;
	}
	free(hypothetical_path_cmd);
	hypothetical_path_cmd = NULL;
	return (real_path);
}

static int	find_path(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strnstr(env[i], "PATH=", 5))
			return (i);
		i++;
	}
	return (-1);
}

static char	*find_real_cmd(char **env, char **cmd_and_flags)
{
	char	**path;
	char	**hypothetical_path_cmd;
	char	*real_path;

	path = ft_split(env[find_path(env)], ':');
	if (!path)
	{
		ft_putendl_fd("malloc failed", STDERR_FILENO);
		return (NULL);
	}
	path[0] = ft_strtrim_improved(path[0], "PATH=");
	if (!path[0])
	{
		free_tab(*path + 1);
		ft_putendl_fd("malloc failed", STDERR_FILENO);
		return (NULL);
	}
	hypothetical_path_cmd = malloc(sizeof (char *) * tablen(path));
	if (!hypothetical_path_cmd)
	{
		free_tab(path);
		ft_putendl_fd("malloc failed", STDERR_FILENO);
		return (NULL);
	}
	if (init_hyp_path(hypothetical_path_cmd, cmd_and_flags, path) == 0)
	{
		// free_tab(*path + 1);
		// free_tab(hypothetical_path_cmd);
		// ft_putendl_fd("malloc failed", STDERR_FILENO);
		return (NULL);
	}
	real_path = find_path_cmd(hypothetical_path_cmd, path);
	free_tab(path);
	return (real_path);
}

static int	manage_child(char *cmd, char **env)
{
	char	**cmd_and_flags;
	char	*path_cmd;

	if (ft_strlen(cmd) == 0)
	{
		ft_putendl_fd("permission denied", STDERR_FILENO);
		return (-1);
	}
	cmd_and_flags = ft_split(cmd, ' ');
	if (!cmd_and_flags)
	{
		ft_putendl_fd("malloc failed", STDERR_FILENO);
		return (-1);
	}
	path_cmd = find_real_cmd(env, cmd_and_flags);
	if (!path_cmd)
	{
		return (-1);
	}
	if (access(path_cmd, X_OK))
	{
		/*fail*/
		return (-1);
	}
	if (execve(path_cmd, cmd_and_flags, env) == -1)
	{
		/*fail*/
		return (-1);
	}
}

static void	manage_first_cmd(int *pipe_fd, char **av, char **env, pid_t *pid)
{
	int	infile;

	if (pipe(pipe_fd) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	pid[0] = fork();
	if (pid[0] == -1)
	{
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (pid[0] == 0)
	{
		infile = open(av[1], O_RDONLY);
		if (infile == -1)
		{
			close(pipe_fd[0]);
			close(pipe_fd[1]);
			perror("open");
			exit(EXIT_FAILURE);
		}
		if (dup2(infile, STDIN_FILENO) == -1 || dup2(pipe_fd[1], STDOUT_FILENO) == -1)
		{
			close(infile);
			close(pipe_fd[0]);
			close(pipe_fd[1]);
			perror("dup2");
			exit(EXIT_FAILURE);
		}
		close(pipe_fd[0]);
		if (manage_child(av[2], env) == -1)
		{
			close(infile);
			close(pipe_fd[0]);
			close(pipe_fd[1]);
			exit(EXIT_FAILURE);
		}
	}
}

static void	manage_last_cmd(int *pipe_fd, char **av, char **env, pid_t *pid)
{
	int	outfile;

	pid[1] = fork();
	if (pid[1] == -1)
	{
		/*fail*/
	}
	if (pid[1] == 0)
	{
		outfile = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (outfile == -1)
		{
			/*fail*/
		}
		if (dup2(pipe_fd[0], STDIN_FILENO) == -1 || dup2(outfile, STDOUT_FILENO) == -1)
		{
			/*fail*/
		}
		close(pipe_fd[1]);
		manage_child(av[3], env);
	}
}

static int	wait_for_pid(pid_t *pid)
{
	int	i;
	int	status;

	i = 0;
	while (pid[i])
	{
		if (waitpid(pid[i], &status, 0) == -1)
		{
			/*fail*/
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
	pid_t	pid[2];
	int		exit_status;

	if (ac != 5)
	{
		ft_putendl_fd("Error\nInvalid number of argument", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	if (!env || !env[0])
	{
		ft_putendl_fd("Error\nNo environment", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	manage_first_cmd(pipe_fd, av, env, pid);
	manage_last_cmd(pipe_fd, av, env, pid);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	exit_status = wait_for_pid(pid);
	exit(exit_status);
}
