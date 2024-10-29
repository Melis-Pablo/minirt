/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_ident.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 14:19:00 by pmelis            #+#    #+#             */
/*   Updated: 2024/10/24 17:52:35 by pmelis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniHope.h"

void	camera_setup(t_camera *camera, t_scene *scene)
{
	t_vec3		temp_up;
	t_vec3		right;

	camera->direction = vec3_normalize(
			vec3_subtract(camera->direction, camera->position));
	temp_up = vec3_create(0, 1, 0);
	right = vec3_normalize(vec3_cross(camera->direction, temp_up));
	camera->up = vec3_normalize(vec3_cross(right, camera->direction));
	if (camera->fov != 180)
		camera->fov = -camera->fov;
	camera->aspect_ratio = (float)scene->width / scene->height;
}

int	acl_case(t_scene *scene, int ident, char *line)
{
	if (ident == A)
	{
		if (scene->ambient)
			return (perror_ret("Error: Ambient light already defined\n"));
		return (get_a(line, scene) != 0);
	}
	else if (ident == C)
	{
		if (scene->camera)
			return (perror_ret("Error: Camera already defined\n"));
		if (get_c(line, scene) != 0)
			return (1);
		camera_setup(scene->camera, scene);
	}
	else if (ident == L)
	{
		if (scene->light_count >= MAX_LIGHTS)
			return (perror_ret("Error: Max lights already defined\n"));
		if (get_l(line, scene) != 0)
			return (1);
		scene->light_count++;
	}
	return (0);
}

int	check_ident(char *line, t_scene *scene)
{
	int	ident;

	ident = check_chars(line);
	if (ident == INVALID)
		return (perror_ret("Error: Invalid identifier\n"));
	else if (ident == COMMENT || ident == EMPTY)
		return (0);
	else if (ident == A || ident == C || ident == L)
		return (acl_case(scene, ident, line));
	else if (ident == PL)
		return (get_pl(line, scene));
	else if (ident == SP)
		return (get_sp(line, scene));
	else if (ident == CY)
		return (get_cy(line, scene));
	else
		printf("new_case\n");
	return (0);
}
