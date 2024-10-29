/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_rgb.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grbuchne <grbuchne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 18:23:38 by grbuchne          #+#    #+#             */
/*   Updated: 2024/10/28 18:24:58 by grbuchne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniHope.h"

int	set_rgb_check(char *value, char c, float *color)
{
	if (!value)
	{
		printf("Error: Missing %c value in RGB\n", c);
		return (1);
	}
	if (is_float(value))
	{
		printf("Error: %c value must be a int\n", c);
		return (1);
	}
	if (ft_set_atof(value, color) != 0)
	{
		printf("Error: %c value must be a number\n", c);
		return (1);
	}
	return (0);
}

int	check_rgb_trailing(char **str, char delim)
{
	char	*value;

	if (!is_whitespace(delim))
	{
		if (delim != '\0')
			return (perror_ret("Error: extra shit\n"));
	}
	value = get_next_value(str, &delim);
	if (value)
		return (perror_ret("Error: extra shit 2\n"));
	return (0);
}

int	set_rgb(t_vec3 *color, char **str)
{
	char	*value;
	char	delim;

	value = get_next_value(str, &delim);
	if (set_rgb_check(value, 'R', &color->x))
		return (1);
	if (delim != ',')
		return (perror_ret("Error: Missing comma after R value in RGB\n"));
	value = get_next_value(str, &delim);
	if (set_rgb_check(value, 'G', &color->y))
		return (1);
	if (delim != ',')
		return (perror_ret("Error: Missing comma after G value in RGB\n"));
	value = get_next_value(str, &delim);
	if (set_rgb_check(value, 'B', &color->z))
		return (1);
	if (color->x < 0 || color->x > 255 || color->y < 0 || color->y > 255
		|| color->z < 0 || color->z > 255)
		return (perror_ret("Error: RGB values must be between 0 and 255\n"));
	normalize_colors(color);
	return (check_rgb_trailing(str, delim));
}
