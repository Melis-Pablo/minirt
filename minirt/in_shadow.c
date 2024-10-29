/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_normed3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 16:18:15 by pmelis            #+#    #+#             */
/*   Updated: 2024/10/14 17:09:16 by pmelis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniHope.h"

int	check_cylinder_intersection(t_ray shadow_ray, t_object object,
	float light_distance, float *t)
{
	const float	shadow_epsilon = 1e-3;

	if (intersect_cylinder(shadow_ray, &object, t)
		&& *t < light_distance - shadow_epsilon)
		return (1);
	return (0);
}

int	check_sphere_intersection(t_ray shadow_ray, t_object object,
	float light_distance, float *t)
{
	const float	shadow_epsilon = 1e-3;

	if (intersect_sphere(shadow_ray, object.s_sphere.center,
			object.s_sphere.radius, t) && *t < light_distance - shadow_epsilon)
		return (1);
	return (0);
}

int	check_plane_intersection(t_ray shadow_ray, t_object object,
	float light_distance, float *t)
{
	const float	shadow_epsilon = 1e-3;

	if (intersect_plane(shadow_ray, object.s_plane.point,
			object.s_plane.normal, t) && *t < light_distance - shadow_epsilon)
		return (1);
	return (0);
}

int	is_in_shadow_loop(t_ray sr, t_scene *scene, float ld)
{
	int		i;
	float	t;

	i = 0;
	while (i < scene->object_count)
	{
		if (scene->objects[i].type == CYLINDER)
		{
			if (check_cylinder_intersection(sr, scene->objects[i], ld, &t))
				return (1);
		}
		else if (scene->objects[i].type == SPHERE)
		{
			if (check_sphere_intersection(sr, scene->objects[i], ld, &t))
				return (1);
		}
		else if (scene->objects[i].type == PLANE)
		{
			if (check_plane_intersection(sr, scene->objects[i], ld, &t))
				return (1);
		}
		i++;
	}
	return (0);
}

int	is_in_shadow(t_vec3 point, t_vec3 light_dir, float light_distance,
	t_scene *scene)
{
	const float	shadow_epsilon = 1e-3;
	t_ray		shadow_ray;

	shadow_ray = (t_ray){
		vec3_add(point, vec3_multiply(light_dir, shadow_epsilon)), light_dir};
	return (is_in_shadow_loop(shadow_ray, scene, light_distance));
}
