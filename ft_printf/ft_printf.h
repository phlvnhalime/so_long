/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpehliva <hpehliva@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 16:57:11 by hpehliva          #+#    #+#             */
/*   Updated: 2024/11/06 18:14:59 by hpehliva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>

int	ft_unsigned_des(unsigned int i);
int	ft_puthex(unsigned long i, char format);
int	ft_putptr(void *ptr);
int	ft_putchar_re(char n);
int	ft_putstr(char *str);
int	ft_putnbr(int i);
int	ft_printf(const char *format, ...);

#endif
