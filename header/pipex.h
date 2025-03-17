/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarzila <abarzila@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 14:43:26 by abarzila          #+#    #+#             */
/*   Updated: 2025/03/17 15:23:30 by abarzila         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H

# define PIPEX_H

# include "../libft/libft.h"
# include "../libft/printf/ft_printf.h"
# include "../libft/printf_err/ft_printf_err.h"
# include <stdio.h>

/*utils.c*/
void	close_perror_exit(int *pipe_fd, int fd, char *message, int exit_status);
void	putendl_exit(char *message, int exit_status);
int		tablen(char **tab);
char	*free_tab(char **tab);
char	*ft_strtrim_improved(char *s1, char const *set);
/*command.c*/
char	*find_real_cmd(char **env, char **cmd_and_flags);

#endif
