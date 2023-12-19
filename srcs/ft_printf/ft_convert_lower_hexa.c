/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_lower_hexa.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibertran <ibertran@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 13:55:54 by ibertran          #+#    #+#             */
/*   Updated: 2023/12/19 06:48:40 by ibertran         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

ssize_t	pf_convert_lower_hexa(va_list *args, t_format *format)
{
	int	nbr;

	if (format->minus || format->period)
		format->zero = false;
	nbr = va_arg(*args, int);
	if (nbr == 0 && format->period && format->precision < 1)
		return (pf_print_decimal_zero(format));
	pf_lower_hexa_maths(format, nbr);
	if (format->minus)
		return (pf_print_lower_hexa_left(format, nbr));
	return (pf_print_lower_hexa(format, nbr));
}

ssize_t	pf_print_lower_hexa(t_format *format, int nbr)
{
	char	*print;
	char	*hexa;
	size_t	i;
	ssize_t	wr;

	print = ft_calloc(format->totallen + 1, sizeof(char));
	if (!print)
		return (-1);
	i = pf_place_padding(format, print);
	if (format->hash && nbr != 0)
		i = ft_strlcat(print, "0x", format->totallen + 1);
	ft_memset(print + i, '0', format->precisionlen);
	wr = -1;
	hexa = ft_uitoa_base(nbr, LOWER_HEXA);
	if (hexa)
	{
		i = ft_strlcat(print, hexa, format->totallen + 1);
		wr = write(format->fd, print, format->totallen);
	}
	free(hexa);
	free(print);
	return (wr);
}

ssize_t	pf_print_lower_hexa_left(t_format *format, int nbr)
{
	char	*print;
	char	*hexa;
	size_t	i;
	ssize_t	wr;

	print = ft_calloc(format->totallen + 1, sizeof(char));
	if (!print)
		return (-1);
	i = 0;
	if (format->hash && nbr != 0)
		i = ft_strlcat(print, "0x", format->totallen + 1);
	ft_memset(print + i, '0', format->precisionlen);
	wr = -1;
	hexa = ft_uitoa_base(nbr, LOWER_HEXA);
	if (hexa)
	{
		i = ft_strlcat(print, hexa, format->totallen + 1);
		ft_memset(print + i, ' ', format->padlen);
		wr = write(format->fd, print, format->totallen);
	}
	free(hexa);
	free(print);
	return (wr);
}

void	pf_lower_hexa_maths(t_format *format, int nbr)
{
	size_t	max;

	max = 0;
	format->arglen = ft_uitoalen_base(nbr, LOWER_HEXA);
	if (format->arglen > format->precision)
		max = format->arglen;
	else
	{
		max = format->precision;
		format->precisionlen = format->precision - format->arglen;
	}
	if (format->width > max + ((2 * (format->hash))) * (nbr != 0))
		format->padlen = format->width - max \
			- ((2 * (format->hash))) * (nbr != 0);
	format->totallen = max + format->padlen \
		+ ((2 * (format->hash))) * (nbr != 0);
}

int	pf_place_padding(t_format *format, char	*print)
{
	if (format->zero)
		ft_memset(print, '0', format->padlen);
	else
		ft_memset(print, ' ', format->padlen);
	return (format->padlen);
}
