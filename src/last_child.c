/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarzila <abarzila@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 16:04:01 by abarzila          #+#    #+#             */
/*   Updated: 2025/02/20 16:28:12 by abarzila         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/pipex.h"

static char	*ft_strjoin_improved(char *s1, char const *s2)
{
	char	*str;
	int		i;
	int		j;

	if (!s1 || !s2)
		return (NULL);
	str = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!str)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
	{
		str[i + j] = s2[j];
		j++;
	}
	str[i + j] = '\0';
	free(s1);
	return (str);
}

void	manage_cmd_last(int *pipe_fd, char **arg, char **env)
{
	char	**cmd_and_flags;
	char	*from_pipe;
	char	*path_cmd;
	int		file_out;

	from_pipe = NULL;
	if (close(pipe_fd[1]))
	{
		/*fail*/
	}
	//lire le resultat envoyé par pipe_fd[1]
	while (1) //A MODIFIER FOR OBVIOUS REASONS//////////////////////////////////////////////////////
	{
		from_pipe = ft_strjoin_improved(from_pipe, get_next_line(pipe_fd[0]));
		if (!from_pipe)
		{
			ft_putendl_fd("Error : last child failed to receive pipe output", STDERR_FILENO);
			exit(EXIT_FAILURE);
		}
	}
	cmd_and_flags = ft_split(arg[2], ' '); //strings de la comd et strings des flags
	//verifier que la commande existe et la recuperer dans le bon path
	path_cmd = find_real_cmd(env, cmd_and_flags);
	if (!path_cmd)
	{
		perror("command failed");
		exit(EXIT_FAILURE);
	}
	//ouvrir le fichier av[3]
	//verifier qu'on a les droits sur la cmd
	if (access(path_cmd, X_OK)) /*the access asked depends on the command*/
	{
		free(path_cmd);
		perror("access failed");
		exit(EXIT_FAILURE);
	}
	//executer la commande av[3] et stocker son resultat dans le fichier av[4]
	file_out = open(arg[4], O_WRONLY | O_CREAT | O_TRUNC);
	if (file_out == -1)
	{
		perror("open pid_2");
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		exit(EXIT_FAILURE);
	}
	if (dup2(file_out, STDOUT_FILENO) == -1)
		{
			perror("dup pid_2");
			close(pipe_fd[0]);
			close(pipe_fd[1]);
			exit(EXIT_FAILURE);
		}
	execve(path_cmd, &arg[3], env);
    perror("execve failed");
}

