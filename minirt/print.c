/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 10:59:52 by pmelis            #+#    #+#             */
/*   Updated: 2024/10/24 17:13:45 by pmelis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniHope.h"

void	print_vec3(t_vec3 vec)
{
	printf("(%f, %f, %f)\n", vec.x, vec.y, vec.z);
}

void	print_data(t_data *data)
{
	printf("img: %p\n", data->img);
	printf("addr: %p\n", data->addr);
	printf("bits_per_pixel: %d\n", data->bits_per_pixel);
	printf("line_length: %d\n", data->line_length);
	printf("endian: %d\n", data->endian);
}

void	print_ray(t_ray *ray)
{
	printf("origin: ");
	print_vec3(ray->origin);
	printf("direction: ");
	print_vec3(ray->direction);
}

void	print_camera(t_camera *camera)
{
	if (!camera)
	{
		printf("No camera\n");
		return ;
	}
	printf("camera:\n");
	printf("	position: ");
	print_vec3(camera->position);
	printf("	direction: ");
	print_vec3(camera->direction);
	printf("	up: ");
	print_vec3(camera->up);
	printf("	fov: %f\n", camera->fov);
	printf("	aspect_ratio: %f\n", camera->aspect_ratio);
}

void	print_scene(t_scene *scene)
{
	int	i;

	i = 0;
	if (!scene)
		perror_ret("No scene\n");
	printf("current scene status:\n");
	printf("anti_aliasing_samples: %d\n", scene->anti_aliasing_samples);
	printf("width: %d\nheight: %d\n", scene->width, scene->height);
	print_camera(scene->camera);
	print_ambient_light(scene->ambient);
	printf(">>>object count: %d<<<\n", scene->object_count);
	while (i < scene->object_count)
	{
		printf("object %d:\n", i);
		print_object(&scene->objects[i]);
		i++;
	}
	i = 0;
	printf(">>>light count: %d<<<\n", scene->light_count);
	while (i < scene->light_count)
	{
		printf("light %d:\n", i);
		print_light(&scene->lights[i]);
		i++;
	}
}
