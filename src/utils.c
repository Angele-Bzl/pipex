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
	}
	if (path_cmd)
	{
		i = 0;
		while (path_cmd[i])
		{
			free(path_cmd[i]);
			i++;
		}
	}
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

static	char	*ft_strtrim_improved(char *s1, char const *set)
{
	int	start;
	int	end;
	int	i;

	if (!s1)
		return (malloc (0));
	i = 0;
	start = -1;
	end = -2;
	while (s1[i] && start == -1)
	{
		if (ft_strchr(set, s1[i]) == NULL)
			start = i;
		i++;
	}
	i = ft_strlen(s1) - 1;
	while (i >= 0 && end == -2)
	{
		if (ft_strchr(set, s1[i]) == NULL)
			end = i;
		i--;
	}
	free(s1);
	if (ft_strlen(s1) == 0)
		return (ft_strdup(s1));
	return (ft_substr(s1, start, (end - start) + 1));
}

char	*find_real_cmd(char *cmd, char **env)
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
	path = ft_split(env[path_index],  ':'); // strings de tous les path
	path[0] = ft_strtrim_improved(path[0], "PATH=");
	hypothetical_path_cmd = malloc(sizeof (char *) * i); // tableau qui va contenir tous les chemins hypothetiques
	cmd_and_flags = ft_split(cmd, ' '); //strings de la comd et strings des flags
	if (!path || !hypothetical_path_cmd || !cmd_and_flags)
	{
		free_all(path, hypothetical_path_cmd, cmd_and_flags);
		return (NULL);
	}
	i = 0;
	while (path[i]) //creer l'hypothese que le fichier est dans chaque path
	{
		hypothetical_path_cmd[i] = ft_strjoin(path[i], cmd_and_flags[0]); //il manque le /
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
			/*free le reste*/
			return (hypothetical_path_cmd[i]);
		}
		i++;
	}
	return (NULL);
}

