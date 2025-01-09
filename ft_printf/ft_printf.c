/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpehliva <hpehliva@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 16:52:26 by hpehliva          #+#    #+#             */
/*   Updated: 2024/11/08 12:32:35 by hpehliva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	implement_keys(va_list args, char format)
{
	int	turn;

	turn = 0;
	if (format == 'c')
		turn = ft_putchar_re(va_arg(args, int));
	else if (format == 's')
		turn = ft_putstr(va_arg(args, char *));
	else if (format == 'p')
		turn = ft_putptr(va_arg(args, void *));
	else if (format == 'x' || format == 'X')
		turn = ft_puthex(va_arg(args, unsigned int), format);
	else if (format == 'd' || format == 'i')
		turn = ft_putnbr(va_arg(args, int));
	else if (format == 'u')
		turn = ft_unsigned_des(va_arg(args, unsigned int));
	else if (format == '%')
		turn = ft_putchar_re('%');
	else
		return (-1);
	return (turn);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		turn;
	int		check;

	va_start(args, format);
	turn = 0;
	while (*format)
	{
		if (*format == '%')
		{
			format++;
			if (*format == '\0')
				break ;
			check = implement_keys(args, *format);
			turn += check;
		}
		else
		{
			check = ft_putchar_re(*format);
			turn += check;
		}
		format++;
	}
	return (va_end(args), turn);
}

// #include <stdio.h>

// int	main(void)
// {
//     // Character
//     ft_printf("Character: %c\n", 'A');
// 	printf("Character: %c\n", 'A');
//     // String
//     ft_printf("String: %s\n", '');
// 	printf("String: %s\n", '');
//     // Pointer
//     int num = 42;
//     ft_printf("Pointer: %p\n", (void *)&num);
// 	printf("Pointer: %p\n", (void *)&num);

//     // Decimal (signed integer)
//     ft_printf("Signed Decimal: %d\n", -123);
// 	printf("Signed Decimal: %d\n", -123);

//     // Integer (another way to print signed integer)
//     ft_printf("Integer: %i\n", 123);
//     printf("Integer: %i\n", 123);

//     // Unsigned integer
//     ft_printf("Unsigned: %u\n", 300);
//     printf("Unsigned: %u\n", 300);

//     // Hexadecimal (lowercase)
//     ft_printf("Hexadecimal (lowercase): %x\n", 255);
//     printf("Hexadecimal (lowercase): %x\n", 255);

//     // Hexadecimal (uppercase)
//     ft_printf("Hexadecimal (uppercase): %X\n", 255);
//     printf("Hexadecimal (uppercase): %X\n", 255);

//     // Percent sign
// 	ft_printf("Percent Sign: %%\n");
//     printf("Percent Sign: %%\n");

//     return (0);
// }
