/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   put_fd.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: tjans <marvin@codam.nl>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/30 13:44:37 by tjans         #+#    #+#                 */
/*   Updated: 2019/11/07 17:38:48 by tjans         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, sizeof(char));
}

void	ft_putstr_fd(char *s, int fd)
{
	if (!s)
		return ;
	write(fd, s, ft_strlen(s));
}

void	ft_putendl_fd(char *s, int fd)
{
	ft_putstr_fd(s, fd);
	ft_putchar_fd('\n', fd);
}

void	ft_putnbr_fd(int n, int fd)
{
	int	div;
	int	digit;

	div = 1000000000;
	if (n < 0)
		ft_putchar_fd('-', fd);
	while (!(n / div) && div > 1)
		div /= 10;
	if (!div)
		ft_putchar_fd('0', fd);
	while (div)
	{
		digit = n / div;
		if (digit < 0)
			digit *= -1;
		ft_putchar_fd(digit + '0', fd);
		if (n < 0)
			n += div * digit;
		else
			n -= div * digit;
		div /= 10;
	}
}
