/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarzila <abarzila@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 14:43:26 by abarzila          #+#    #+#             */
/*   Updated: 2025/03/18 11:23:52 by abarzila         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H

# define PIPEX_BONUS_H

# include "../libft/libft.h"
# include "../libft/printf/ft_printf.h"
# include "../libft/printf_err/ft_printf_err.h"
# include <sys/wait.h>

typedef struct s_user_env
{
	int		ac;
	char	**av;
	char	**env;
}			t_user_env;

/*utils00_bonus.c*/
void	close_perror_exit(int *pipe_fd, int fd, char *message, pid_t *pid);
void	putendl_exit(char *message, int exit_status, pid_t *pid);
int		tablen(char **tab);
char	*free_tab(char **tab);
char	*ft_strtrim_improved(char *s1, char const *set);
/*utils01_bonus.c*/
void	close_all(int *pipe_fd, int file);
void	init_struct_env(t_user_env *user_env, int ac, char **av, char **env);
int		wait_for_pid(pid_t *pid, int ac);
int		check_env_av(int ac, char **env);
/*command_bonus.c*/
char	*find_real_cmd(char **env, char **cmd_and_flags);

#endif
