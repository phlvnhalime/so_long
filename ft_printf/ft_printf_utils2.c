/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpehliva <hpehliva@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 09:51:14 by hpehliva          #+#    #+#             */
/*   Updated: 2024/11/09 09:51:17 by hpehliva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putchar_re(char n)
{
	return (write(1, &n, 1));
}

int	ft_putstr(char *str)
{
	int	turn;
	int	check;

	turn = 0;
	if (str == NULL)
		return (write(1, "(null)", 6));
	while (*str)
	{
		check = ft_putchar_re(*str++);
		if (check == -1)
			return (-1);
		turn += check;
	}
	return (turn);
}

int	ft_putnbr(int i)
{
	int	check;
	int	turn;

	turn = 0;
	if (i == -2147483648)
		return (ft_putstr("-2147483648"));
	if (i < 0)
	{
		turn += ft_putchar_re('-');
		if (turn == -1)
			return (-1);
		i = -i;
	}
	if (i >= 10)
	{
		check = ft_putnbr(i / 10);
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
