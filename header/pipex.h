/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarzila <abarzila@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 14:43:26 by abarzila          #+#    #+#             */
/*   Updated: 2025/03/11 14:19:40 by abarzila         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H

# define PIPEX_H

# include "../libft/libft.h"
# include "../libft/printf/ft_printf.h"
# include "../libft/printf_err/ft_printf_err.h"
# include <sys/wait.h>

/*utils.c*/
int		tablen(char **tab);
void	free_tab(char **tab);
char	*ft_strtrim_improved(char *s1, char const *set);

#endif
