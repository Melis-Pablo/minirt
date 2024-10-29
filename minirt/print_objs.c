/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_objs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 10:27:07 by pmelis            #+#    #+#             */
/*   Updated: 2024/10/24 17:24:28 by pmelis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniHope.h"

void	sp_print(t_object *object)
{
	printf("sphere:\n");
	printf("	center: ");
	print_vec3(object->s_sphere.center);
	printf("	radius: %f\n", object->s_sphere.radius);
}

void	pl_print(t_object *object)
{
	printf("plane:\n");
	printf("	point: ");
	print_vec3(object->s_plane.point);
	printf("	normal: ");
	print_vec3(object->s_plane.normal);
}

void	cy_print(t_object *object)
{
	printf("cylinder:\n");
	printf("	center: ");
	print_vec3(object->s_cylinder.center);
	printf("	axis: ");
	print_vec3(object->s_cylinder.axis);
	printf("	radius: %f\n", object->s_cylinder.radius);
	printf("	height: %f\n", object->s_cylinder.height);
	printf("	base_center: ");
	print_vec3(object->s_cylinder.base_center);
}

void	print_object(t_object *object)
{
	if (object->type == SPHERE)
		sp_print(object);
	else if (object->type == PLANE)
		pl_print(object);
	else if (object->type == CYLINDER)
		cy_print(object);
	printf("	color: ");
	print_vec3(object->color);
}
