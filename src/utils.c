#include "pipex.h"

void	free_all(char *path, char *path_cmd, char **cmd_and_flags)
{
	int	i;

	if (path)
		free(path);
	if (path_cmd)
		free(path_cmd);
	if (cmd_and_flags)
	{
		i = 0;
		while (cmd_and_flags[i])
		{
			free(cmd_and_flags[i]);
			i++;
		}
	}
}

char	*extract_cmd(char *cmd_flag)
{
	char	**cmd;

	cmd = ft_split(cmd_flag, ' ');
	return (cmd);
}


char	*real_cmd(char *cmd, char **env)
{
	int		i;
	int		path_index;
	char	**path;
	char	**hypothetical_path_cmd;
	char	**cmd_and_flags;

	i = 0;
	while (env[i]) // trouver la liste de path
	{
		if (ft_strnstr(env[i], "PATH=", 5))
			path_index = i;
		i++;
	}
	path = ft_split(env[path_index], ":"); // strings de tous les path
	hypothetical_path_cmd = malloc(sizeof (char *) * i); // tableau qui va contenir tous les chemins hypothetiques
	cmd_and_flags = extract_cmd(cmd); //strings de la comd et strings des flags
	if (!path || !hypothetical_path_cmd || !cmd_and_flags)
	{
		free_all(path, hypothetical_path_cmd, cmd_and_flags);
		return (NULL);
	}
	i = 0;
	while (path[i]) //creer l'hypothese que le fichier est dans chaque path
	{
		hypothetical_path_cmd[i] = ft_strjoin(path[i], cmd_and_flags[0]);
		if (!hypothetical_path_cmd[i])
		{
			free_all(path, hypothetical_path_cmd, cmd_and_flags);
			return (NULL);
		}
		i++;
	}
	i = 0;
	while (path[i]) // verifier que le fichier de cmd est dans un path jusqu'a le trouver
	{
		if(!access(hypothetical_path_cmd[i], F_OK))
		{
			/*free le reste*/
			return (hypothetical_path_cmd[i]);
		}
		i++;
	}
	return (NULL);
}
