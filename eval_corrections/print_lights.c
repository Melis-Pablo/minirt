/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_lights.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 10:27:42 by pmelis            #+#    #+#             */
/*   Updated: 2024/10/24 17:24:50 by pmelis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniHope.h"

void	print_light(t_light *light)
{
	printf("	position: ");
	print_vec3(light->position);
	printf("	color: ");
	print_vec3(light->color);
	printf("	intensity: %f\n", light->intensity);
}

void	print_ambient_light(t_ambient_light *ambient)
{
	if (!ambient)
	{
		printf("No ambient light\n");
		return ;
	}
	printf("ambient light:\n");
	printf("	intensity: %f\n", ambient->intensity);
	printf("	color: ");
	print_vec3(ambient->color);
}
