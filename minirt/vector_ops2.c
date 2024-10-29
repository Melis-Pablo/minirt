/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_ops2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 09:56:18 by pmelis            #+#    #+#             */
/*   Updated: 2024/10/12 20:38:27 by pmelis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniHope.h"

float	vec3_dot(t_vec3 a, t_vec3 b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

float	vec3_length(t_vec3 v)
{
	return (sqrt(vec3_dot(v, v)));
}

t_vec3	vec3_normalize(t_vec3 v)
{
	return (vec3_multiply(v, 1.0f / vec3_length(v)));
}

void	normalize_colors(t_vec3 *colors)
{
	colors->x /= 255.0f;
	colors->y /= 255.0f;
	colors->z /= 255.0f;
}

t_vec3	vec3_cross(t_vec3 a, t_vec3 b)
{
	return (vec3_create(a.y * b.z - a.z * b.y,
			a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x));
}
