/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters_acl.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 10:51:33 by pmelis            #+#    #+#             */
/*   Updated: 2024/10/24 18:16:54 by pmelis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniHope.h"

int	get_a(char *line, t_scene *scene)
{
	char			*value;
	char			delim;

	scene->ambient = malloc(sizeof(t_ambient_light));
	if (!scene->ambient)
		return (perror_ret("Error: Memory allocation failed\n"));
	value = get_next_value(&line, &delim);
	value = get_next_value(&line, &delim);
	if (!value)
		return (perror_ret("Error: Missing ambient light intensity\n"));
	if (ft_set_atof(value, &scene->ambient->intensity) != 0)
		return (perror_ret("Error: Invalid ambient light intensity\n"));
	if (scene->ambient->intensity < 0 || scene->ambient->intensity > 1)
		return (perror_ret(
				"Error: Ambient light intensity must be between 0.0-1.0\n"));
	if (set_rgb(&scene->ambient->color, &line))
		return (perror_ret("Error: Invalid RGB values for ambient light\n"));
	return (0);
}

int	get_c(char *line, t_scene *scene)
{
	char		*value;
	char		delim;

	scene->camera = malloc(sizeof(t_camera));
	if (!scene->camera)
		return (perror_ret("Error: Memory allocation failed\n"));
	value = get_next_value(&line, &delim);
	if (set_xyz(&scene->camera->position, &line) != 0)
		return (perror_ret("Error: Invalid camera position\n"));
	if (set_nxyz(&scene->camera->direction, &line) != 0)
		return (perror_ret("Error: Invalid camera direction\n"));
	value = get_next_value(&line, &delim);
	if (!value)
		return (perror_ret("Error: Missing camera FOV\n"));
	scene->camera->fov = ft_atoi(value);
	if (scene->camera->fov < 0 || scene->camera->fov > 180)
		return (perror_ret("Error: FOV must be between 0 and 180\n"));
	return (0);
}

int	get_l(char *line, t_scene *scene)
{
	char	*value;
	char	delim;

	value = get_next_value(&line, &delim);
	if (set_xyz(&scene->lights[scene->light_count].position, &line) != 0)
		return (perror_ret("Error: Invalid light position\n"));
	value = get_next_value(&line, &delim);
	if (!value)
		return (perror_ret("Error: Missing light brightness intensity\n"));
	if (ft_set_atof(value, &scene->lights[scene->light_count].intensity) != 0)
		return (perror_ret("Error: Invalid light brightness intensity\n"));
	if (scene->lights[scene->light_count].intensity < 0
		|| scene->lights[scene->light_count].intensity > 1)
		return (perror_ret(
				"Error: Light brightness intensity must be between 0.0-1.0\n"));
	if (set_rgb(&scene->lights[scene->light_count].color, &line) != 0)
		return (perror_ret("Error: Invalid light color\n"));
	return (0);
}
