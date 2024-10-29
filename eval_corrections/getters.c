/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grbuchne <grbuchne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 14:45:51 by pmelis            #+#    #+#             */
/*   Updated: 2024/10/28 17:08:45 by grbuchne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniHope.h"

int	get_pl(char *line, t_scene *scene)
{
	char	*value;
	char	delim;

	scene->objects[scene->object_count].type = PLANE;
	value = get_next_value(&line, &delim);
	(void)value;
	if (set_xyz(&scene->objects[scene->object_count].s_plane.point, &line) != 0)
		return (perror_ret("Error: Invalid plane point\n"));
	if (set_nxyz(&scene->objects[scene->object_count].s_plane.normal,
			&line) != 0)
		return (perror_ret("Error: Invalid plane normal\n"));
	if (set_rgb(&scene->objects[scene->object_count].color, &line) != 0)
		return (perror_ret("Error: Invalid plane color\n"));
	scene->object_count++;
	return (0);
}

int	get_sp(char *line, t_scene *scene)
{
	char		*value;
	char		delim;

	scene->objects[scene->object_count].type = SPHERE;
	value = get_next_value(&line, &delim);
	if (set_xyz(&scene->objects[scene->object_count].s_sphere.center,
			&line) != 0)
		return (perror_ret("Error: Invalid sphere center\n"));
	value = get_next_value(&line, &delim);
	if (!value)
		return (perror_ret("Error: Missing sphere diameter\n"));
	if (!is_whitespace(delim))
		return (perror_ret("Error: extra shit\n"));
	if (ft_set_atof(value,
			&scene->objects[scene->object_count].s_sphere.radius) != 0)
		return (perror_ret("Error: Sphere diameter must be a number\n"));
	scene->objects[scene->object_count].s_sphere.radius /= 2;
	if (scene->objects[scene->object_count].s_sphere.radius <= 0)
		return (perror_ret("Error: Sphere diameter must be positive\n"));
	if (set_rgb(&scene->objects[scene->object_count].color, &line) != 0)
		return (perror_ret("Error: Invalid sphere color\n"));
	scene->object_count++;
	return (0);
}

int	set_cylinder_attributes(t_object *obj, char **line)
{
	char	*value;
	char	delim;

	value = get_next_value(line, &delim);
	if (!is_whitespace(delim))
		return (perror_ret("Error: extra shit\n"));
	if (!value)
		return (perror_ret("Error: Missing cylinder diameter\n"));
	if (ft_set_atof(value, &obj->s_cylinder.radius) != 0)
		return (perror_ret("Error: Cylinder diameter must be a number\n"));
	obj->s_cylinder.radius /= 2;
	value = get_next_value(line, &delim);
	if (!is_whitespace(delim))
		return (perror_ret("Error: extra shit\n"));
	if (!value)
		return (perror_ret("Error: Missing cylinder height\n"));
	if (ft_set_atof(value, &obj->s_cylinder.height) != 0)
		return (perror_ret("Error: Cylinder height must be a number\n"));
	if (obj->s_cylinder.radius <= 0 || obj->s_cylinder.height <= 0)
		return (
			perror_ret("Error: Cylinder radius and height must be positive\n"));
	return (0);
}

int	get_cy(char *line, t_scene *scene) //make error checks to free
{
	char		*value;
	char		delim;

	scene->objects[scene->object_count].type = CYLINDER;
	value = get_next_value(&line, &delim);
	(void)value;
	if (set_xyz(&scene->objects[scene->object_count].s_cylinder.center, &line))
		return (perror_ret("Error: Invalid cylinder center\n"));
	if (set_nxyz(&scene->objects[scene->object_count].s_cylinder.axis, &line))
		return (perror_ret("Error: Invalid cylinder axis\n"));
	scene->objects[scene->object_count].s_cylinder.axis
		= vec3_normalize(scene->objects[scene->object_count].s_cylinder.axis);
	if (set_cylinder_attributes(&scene->objects[scene->object_count], &line))
		return (perror_ret("Error: Invalid cylinder attributes\n"));
	if (set_rgb(&scene->objects[scene->object_count].color, &line))
		return (perror_ret("Error: Invalid cylinder color\n"));
	scene->objects[scene->object_count].s_cylinder.base_center
		= vec3_subtract(scene->objects[scene->object_count].s_cylinder.center,
			vec3_multiply(scene->objects[scene->object_count].s_cylinder.axis,
				scene->objects[scene->object_count].s_cylinder.height / 2));
	scene->object_count++;
	return (0);
}
