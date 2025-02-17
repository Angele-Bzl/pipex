/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarzila <abarzila@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 16:12:23 by abarzila          #+#    #+#             */
/*   Updated: 2025/02/17 16:54:49 by abarzila         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	is_real_cmd(int **arg, char **env)
{
	int		i;
	int		path_index;
	char	*path;
	char	*path_cmd;

	i = 0;
	while (env[i]) // trouver la liste de path
	{
		if (ft_strnstr(env[i], "PATH=", 5))
			path_index = i;
		i++;
	}
	path = ft_split(env[path_index], ":");
	path_cmd = malloc(sizeof (char *) * i);
	if (!path || !path_cmd)
	{
		free_all();
		return (0);
	}
	/*PENSER A RETIRER LES FLAGS DU ARG[1]*/
	i = 0;
	while (path[i]) //creer l'hypothese que le fichier est dans chaque path
	{
		path_cmd[i] = ft_strjoin(path[i], arg[1]);
		if (!path_cmd[i])
		{
			free_all();
			return (0);
		}
		i++;
	}
	i = 0;
	while (path[i]) // verifier que le fichier est dans un path jusqu'a le trouver
	{
		if(!access(path_cmd[i], F_OK))
		{
			break ;
		}
		i++;
	}
}

void	process_is_parent(int *pipe_fd, char **arg, char **env)
{
	int	i;

	close(pipe_fd[0]);
	//ouvrir le premier fichier av[1]
	if (access(arg[0], F_OK) || open(arg[0], O_APPEND) == -1)
	{
		perror(errno);
		exit(EXIT_FAILURE);
	}
	//verifier que la commande existe
	if (!is_real_cmd(arg, env))
	{
		free_all();
		perror(errno);
		exit(EXIT_FAILURE);
	}
	//verifier qu'on a les droits sur le fichier
	if (access(arg[0], R_OK)) /*the access asked depends on the command*/
	{
		perror(errno);
		exit(EXIT_FAILURE);
	}
	//executer la commande arg[1] sur le fichier arg[0]
	if (execve(arg[0], arg, NULL) == -1)
	{
        perror("execve failed");
    }
	//envoyer ce resultat dans le pipe
}
