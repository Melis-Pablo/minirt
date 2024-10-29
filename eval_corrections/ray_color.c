/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grbuchne <grbuchne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 15:02:31 by pmelis            #+#    #+#             */
/*   Updated: 2024/10/18 18:04:08 by grbuchne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniHope.h"

t_vec3	ray_color_ret(t_ray ray, t_scene *scene)
{
	t_vec3		background_color;
	t_vec3		ambient_contribution;
	t_ray_ret	ret;

	ret.unit_direction = vec3_normalize(ray.direction);
	ret.t_background = 0.5f * (ret.unit_direction.y + 1.0f);
	ret.white = vec3_create(1.0f, 1.0f, 1.0f);
	ret.blue = vec3_create(0.5f, 0.7f, 1.0f);
	background_color = vec3_add(vec3_multiply(ret.white,
				1.0f - ret.t_background),
			vec3_multiply(ret.blue, ret.t_background));
	ambient_contribution = vec3_multiply(scene->ambient->color,
			scene->ambient->intensity);
	return (vec3_add(background_color, ambient_contribution));
}

void	ray_color_loop2_in(t_scene *scene, t_ray_color_calc *calc, int j)
{
	calc->light_dir = vec3_subtract(scene->lights[j].position,
			calc->hit_point);
	calc->light_distance = vec3_length(calc->light_dir);
	calc->light_dir = vec3_normalize(calc->light_dir);
	if (!is_in_shadow(vec3_add(calc->hit_point,
				vec3_multiply(calc->normal, 0.001)),
			calc->light_dir, calc->light_distance, scene))
	{
		calc->diffuse = fmaxf(vec3_dot(calc->normal,
					calc->light_dir), 0.0f);
		calc->diffuse_color = vec3_multiply_components(
				scene->objects[calc->closest_object].color,
				scene->lights[j].color);
		calc->color = vec3_add(calc->color,
				vec3_multiply(calc->diffuse_color,
					calc->diffuse * scene->lights[j].intensity));
	}
}

void	ray_color_loop2(t_scene *scene, t_ray_color_calc *calc)
{
	int		j;
	t_vec3	ambient_contribution;

	j = 0;
	ambient_contribution = vec3_multiply(scene->ambient->color,
			scene->ambient->intensity);
	calc->color = vec3_multiply_components(ambient_contribution,
			scene->objects[calc->closest_object].color);
	while (j < scene->light_count)
	{
		ray_color_loop2_in(scene, calc, j);
		j++;
	}
}

t_vec3	closest_calc(t_scene *scene, t_ray_color_calc *calc, t_ray *ray)
{
	calc->hit_point = vec3_add(ray->origin,
			vec3_multiply(ray->direction, calc->closest_t));
	if (scene->objects[calc->closest_object].type == SPHERE)
	{
		calc->normal = vec3_normalize(vec3_subtract(calc->hit_point,
					scene->objects[calc->closest_object].s_sphere.center));
	}
	else if (scene->objects[calc->closest_object].type == PLANE)
		calc->normal = scene->objects[calc->closest_object].s_plane.normal;
	else if (scene->objects[calc->closest_object].type == CYLINDER)
		calc->normal = get_cylinder_normal(calc->hit_point,
				scene->objects[calc->closest_object]);
	calc->color = vec3_create(0.0f, 0.0f, 0.0f);
	ray_color_loop2(scene, calc);
	calc->max_component = fmaxf(calc->color.x,
			fmaxf(calc->color.y, calc->color.z));
	if (calc->max_component > 1.0f)
		calc->color = vec3_multiply(calc->color, 1.0f
				/ calc->max_component);
	return (calc->color);
}

t_vec3	ray_color(t_ray ray, t_scene *scene)
{
	t_ray_color_calc	calc;

	calc.closest_t = INFINITY;
	calc.closest_object = -1;
	ray_color_loop(scene, &ray, &calc);
	if (calc.closest_object != -1)
		return (closest_calc(scene, &calc, &ray));
	return (ray_color_ret(ray, scene));
}
