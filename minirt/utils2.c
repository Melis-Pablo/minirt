/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 12:09:02 by pmelis            #+#    #+#             */
/*   Updated: 2024/10/25 17:07:48 by pmelis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniHope.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	ft_is_num(const char *str)
{
	while (*str)
	{
		if (!ft_isdigit(*str) && *str != '.' && *str != '+' && *str != '-')
			return (0);
		str++;
	}
	return (1);
}

int	ft_set_atof(const char	*str, float *result_value)
{
	long	int_part;
	double	dec_part;
	double	power;
	int		sign;

	int_part = 0;
	dec_part = 0.0;
	power = 1.0;
	sign = 1;
	if (!ft_is_num(str))
		return (1);
	while (*str == '+' || *str == '-')
		if (*str++ == '-')
			sign = -sign;
	while (*str != '.' && *str)
		int_part = (int_part * 10) + (*str++ - 48);
	if (*str == '.')
		str++;
	while (*str)
	{
		power /= 10;
		dec_part = dec_part + (*str++ - 48) * power;
	}
	*result_value = (float)((int_part + dec_part) * sign);
	return (0);
}

char	*ft_strcpy(char *dest, const char *src)
{
	char	*ptr;

	ptr = dest;
	while (*src)
		*ptr++ = *src++;
	*ptr = '\0';
	return (dest);
}
