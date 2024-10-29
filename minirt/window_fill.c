/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_fill.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 13:25:36 by pmelis            #+#    #+#             */
/*   Updated: 2024/10/15 11:34:09 by pmelis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniHope.h"

void	fill_window(t_data img, t_scene *scene)
{
	int		j;
	int		i;
	int		c;
	t_vec3	color;
	t_vec3	icolor;

	j = scene->height - 1;
	while (j >= 0)
	{
		i = 0;
		while (i < scene->width)
		{
			color = anti_alias_pixel(i, j, scene->anti_aliasing_samples, scene);
			icolor.x = (int)(255.99 * fminf(color.x, 1.0f));
			icolor.y = (int)(255.99 * fminf(color.y, 1.0f));
			icolor.z = (int)(255.99 * fminf(color.z, 1.0f));
			c = create_trgb(icolor.x, icolor.y, icolor.z);
			my_mlx_pixel_put(&img, i, j, c);
			++i;
		}
		--j;
	}
}

t_vec3	anti_alias_pixel(int i, int j, int samples, t_scene *scene)
{
	float	u;
	float	v;
	t_ray	ray;
	int		s;
	t_vec3	color;

	color = vec3_create(0, 0, 0);
	s = 0;
	while (s < samples)
	{
		u = (float)(i + ((float)rand() / (float)RAND_MAX)) / (scene->width - 1);
		v = (float)(j + ((float)rand() / (float)RAND_MAX))
			/ (scene->height - 1);
		ray = get_ray(u, v, *scene->camera);
		color = vec3_add(color, ray_color(ray, scene));
		s++;
	}
	return (vec3_multiply(color, 1.0f / samples));
}

int	t_calc(t_ray ray, t_object *obj, float *t0, float *t1)
{
	t_vec3		oc;
	float		a;
	float		b;
	float		c;
	float		discriminant;

	oc = vec3_subtract(ray.origin, obj->s_cylinder.center);
	a = vec3_dot(ray.direction, ray.direction)
		- pow(vec3_dot(ray.direction, obj->s_cylinder.axis), 2);
	b = 2 * (vec3_dot(ray.direction, oc)
			- vec3_dot(ray.direction, obj->s_cylinder.axis)
			* vec3_dot(oc, obj->s_cylinder.axis));
	c = vec3_dot(oc, oc) - pow(vec3_dot(oc, obj->s_cylinder.axis), 2)
		- obj->s_cylinder.radius * obj->s_cylinder.radius;
	discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
		return (0);
	*t0 = (-b - sqrt(discriminant)) / (2 * a);
	*t1 = (-b + sqrt(discriminant)) / (2 * a);
	return (1);
}

float	y_calc(t_ray ray, t_object *obj, float t)
{
	float	y;

	y = vec3_dot(vec3_subtract(vec3_add(ray.origin,
					vec3_multiply(ray.direction, t)), obj->s_cylinder.center),
			obj->s_cylinder.axis);
	return (y);
}

int	intersect_cylinder(t_ray ray, t_object *obj, float *t)
{
	const float	epsilon = 1e-4;
	float		t0;
	float		t1;
	float		y0;
	float		y1;

	if (t_calc(ray, obj, &t0, &t1) == 0)
		return (0);
	y0 = y_calc(ray, obj, t0);
	y1 = y_calc(ray, obj, t1);
	if (y0 < -epsilon)
	{
		if (y1 < -epsilon)
			return (0);
		t0 = t0 + (t1 - t0) * (-epsilon - y0) / (y1 - y0);
	}
	else if (y0 > obj->s_cylinder.height + epsilon)
	{
		if (y1 > obj->s_cylinder.height + epsilon)
			return (0);
		t0 = t0 + (t1 - t0)
			* (obj->s_cylinder.height + epsilon - y0) / (y1 - y0);
	}
	*t = t0;
	return (*t > epsilon);
}
