/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grbuchne <grbuchne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 14:38:03 by pmelis            #+#    #+#             */
/*   Updated: 2024/10/28 18:48:50 by grbuchne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniHope.h"

char	*get_next_value(char **str, char *delim)
{
	char	*start;

	while (is_whitespace(**str))
		(*str)++;
	start = *str;
	while (**str && !is_whitespace(**str) && **str != ',')
		(*str)++;
	if (start == *str)
		return (NULL);
	*delim = **str;
	if (**str == ',')
	{
		**str = '\0';
		(*str)++;
	}
	else if (**str)
	{
		**str = '\0';
		(*str)++;
	}
	return (start);
}

int	is_normal(t_vec3 *dir)
{
	if (dir->x < -1 || dir->x > 1 || dir->y < -1 || dir->y > 1
		|| dir->z < -1 || dir->z > 1)
		return (1);
	return (0);
}

int	end_coord(t_vec3 *dir, char delim)
{
	if (is_normal(dir) != 0)
		return (perror_ret("Error: Normal vector components range (-1, 1)\n"));
	if (!is_whitespace(delim))
		return (perror_ret("Error: extra shit\n"));
	return (0);
}

int	set_nxyz(t_vec3 *dir, char **str)
{
	char	*value;
	char	delim;

	value = get_next_value(str, &delim);
	if (!value)
		return (perror_ret("Error: Missing x value in normal vector\n"));
	if (ft_set_atof(value, &dir->x) != 0)
		return (perror_ret ("Error: Normal vector must be a number\n"));
	if (delim != ',')
		return (perror_ret("Error: Missing comma in normal vector\n"));
	value = get_next_value(str, &delim);
	if (!value)
		return (perror_ret("Error: Missing y value in normal vector\n"));
	if (ft_set_atof(value, &dir->y) != 0)
		return (perror_ret("Error: Normal vector must be a number\n"));
	if (delim != ',')
		return (perror_ret("Error: Missing comma in normal vector\n"));
	value = get_next_value(str, &delim);
	if (!value)
		return (perror_ret("Error: Missing z value in normal vector\n"));
	if (ft_set_atof(value, &dir->z) != 0)
		return (perror_ret("Error: Normal vector must be a number\n"));
	return (end_coord(dir, delim));
}

int	set_xyz(t_vec3 *coor, char **str)
{
	char	*value;
	char	delim;

	value = get_next_value(str, &delim);
	if (!value)
		return (perror_ret("Error: Missing x coordinate\n"));
	if (ft_set_atof(value, &coor->x) != 0)
		return (perror_ret("Error: x coordinate must be a number\n"));
	if (delim != ',')
		return (perror_ret("Error: Missing comma after x coordinate\n"));
	value = get_next_value(str, &delim);
	if (!value)
		return (perror_ret("Error: Missing y coordinate\n"));
	if (ft_set_atof(value, &coor->y) != 0)
		return (perror_ret("Error: y coordinate must be a number\n"));
	if (delim != ',')
		return (perror_ret("Error: Missing comma after y coordinate\n"));
	value = get_next_value(str, &delim);
	if (!value)
		return (perror_ret("Error: Missing z coordinate\n"));
	if (ft_set_atof(value, &coor->z) != 0)
		return (perror_ret("Error: z coordinate must be a number\n"));
	if (!is_whitespace(delim))
		return (perror_ret("Error: extra shit\n"));
	return (0);
}
