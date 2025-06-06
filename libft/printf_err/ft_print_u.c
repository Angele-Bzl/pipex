/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_u.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarzila <abarzila@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 10:39:35 by abarzila          #+#    #+#             */
/*   Updated: 2025/03/03 10:56:14 by abarzila         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_err.h"

static void	ft_putnbr_fd_printf(int n, int fd, int *count)
{
	char	mod;

	if (n == -2147483648)
	{
		write(fd, "-2147483648", 11);
		count += 11;
		return ;
	}
	if (n < 0)
	{
		write(fd, "-", 1);
		(*count)++;
		n *= -1;
	}
	if (n >= 10)
	{
		ft_putnbr_fd_printf(n / 10, fd, count);
	}
	mod = (n % 10) + 48;
	write(fd, &mod, 1);
	(*count)++;
}

void	print_u(va_list arg, int *count)
{
	unsigned int	u;
	unsigned int	mod;

	u = va_arg(arg, unsigned int);
	if (u >= 10)
	{
		ft_putnbr_fd_printf(u / 10, 2, count);
	}
	mod = (u % 10) + 48;
	write(2, &mod, 1);
	(*count)++;
}
