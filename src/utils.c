#include "../header/pipex.h"

void	free_all(char **path, char **path_cmd, char **cmd_and_flags)
{
	int	i;

	if (path)
	{
		i = 0;
		while (path[i])
		{
			free(path[i]);
			i++;
		}
		// free(path);
	}
	if (path_cmd)
	{
		i = 0;
		while (path_cmd[i])
		{
			free(path_cmd[i]);
			i++;
		}
		// free(path_cmd);
	}
	if (cmd_and_flags)
	{
		i = 0;
		while (cmd_and_flags[i])
		{
			free(cmd_and_flags[i]);
			i++;
		}
		// free(cmd_and_flags);
	}
}

// static void	free_almost_all(char **path, char **path_cmd, int good, char **cmd_and_flags)
// {
// 	int	i;

// 	if (path)
// 	{
// 		i = 0;
// 		while (path[i])
// 		{
// 			free(path[i]);
// 			i++;
// 		}
// 	}
// 	if (path_cmd)
// 	{
// 		i = 0;
// 		while (path_cmd[i])
// 		{
// 			if (i != good)
// 				free(path_cmd[i]);
// 			i++;
// 		}
// 	}
// 	if (cmd_and_flags)
// 	{
// 		i = 0;
// 		while (cmd_and_flags[i])
// 		{
// 			free(cmd_and_flags[i]);
// 			i++;
// 		}
// 	}
// }

char	*find_real_cmd(char **env, char **cmd_and_flags)
{
	int		i;
	int		path_index;
	char	**path;
	char	**hypothetical_path_cmd;

	i = 0;
	while (env[i]) // trouver la liste de path
	{
		if (ft_strnstr(env[i], "PATH=", 5))
			path_index = i;
		i++;
	}
	path = ft_split(env[path_index],  ':'); // strings de tous les path
	path[0] = ft_strtrim(path[0], "PATH=");
	hypothetical_path_cmd = malloc(sizeof (char *) * i); // tableau qui va contenir tous les chemins hypothetiques
	if (!path || !hypothetical_path_cmd || !cmd_and_flags)
	{
		free_all(path, hypothetical_path_cmd, cmd_and_flags);
		return (NULL);
	}
	i = 0;
	while (path[i]) //creer l'hypothese que le fichier est dans chaque path
	{
		hypothetical_path_cmd[i] = ft_strjoin(ft_strjoin(path[i], "/"), cmd_and_flags[0]);
		if (!hypothetical_path_cmd[i])
		{
			free_all(path, hypothetical_path_cmd, cmd_and_flags);
			return (NULL);
		}
		i++;
	}
	i = 0;
	while (path[i]) // verifier que la cmd existe et qu'on a le droit de l'exec
	{
		if(!access(hypothetical_path_cmd[i], X_OK))
		{
			// free_almost_all(path, hypothetical_path_cmd, i, cmd_and_flags);
			return (hypothetical_path_cmd[i]);
		}
		i++;
	}
	free_all(path, hypothetical_path_cmd, cmd_and_flags);
	return (NULL);
}

