/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpehliva <hpehliva@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 09:50:52 by hpehliva          #+#    #+#             */
/*   Updated: 2024/11/09 09:50:59 by hpehliva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_unsigned_des(unsigned int i)
{
	int	check;
	int	turn;

	turn = 0;
	if (i >= 10)
	{
		check = ft_unsigned_des(i / 10);
		if (check == -1)
			return (-1);
		turn += check;
	}
	check = ft_putchar_re((i % 10) + '0');
	if (check == -1)
		return (-1);
	turn += check;
	return (turn);
}

int	ft_puthex(unsigned long i, char format)
{
	int		turn;
	char	*base;

	turn = 0;
	if (format == 'x')
		base = "0123456789abcdef";
	else
		base = "0123456789ABCDEF";
	if (i >= 16)
	{
		turn += ft_puthex((i / 16), format);
		if (turn == -1)
			return (-1);
	}
	if (ft_putchar_re(base[i % 16]) == -1)
		return (-1);
	return (turn + 1);
}

int	ft_putptr(void *ptr)
{
	int	turn;
	int	check;

	if (ptr == NULL)
		return (ft_putstr("0x0"));
	turn = ft_putstr("0x");
	if (turn == -1)
		return (-1);
	check = ft_puthex((unsigned long)ptr, 'x');
	if (check == -1)
		return (-1);
	return (turn + check);
}
