/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_ops.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 09:53:49 by pmelis            #+#    #+#             */
/*   Updated: 2024/10/12 09:54:11 by pmelis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniHope.h"

t_vec3	vec3_create(float x, float y, float z)
{
	return ((t_vec3){x, y, z});
}

t_vec3	vec3_add(t_vec3 a, t_vec3 b)
{
	return (vec3_create(a.x + b.x, a.y + b.y, a.z + b.z));
}

t_vec3	vec3_subtract(t_vec3 a, t_vec3 b)
{
	return (vec3_create(a.x - b.x, a.y - b.y, a.z - b.z));
}

t_vec3	vec3_multiply(t_vec3 v, float s)
{
	return (vec3_create(v.x * s, v.y * s, v.z * s));
}

t_vec3	vec3_multiply_components(t_vec3 a, t_vec3 b)
{
	return (vec3_create(a.x * b.x, a.y * b.y, a.z * b.z));
}
