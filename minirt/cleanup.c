/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 16:40:31 by pmelis            #+#    #+#             */
/*   Updated: 2024/10/24 18:09:34 by pmelis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniHope.h"

// perror(msg);
int	perror_ret(char *msg)
{
	printf("%s", msg);
	return (1);
}

int	free_scene(t_scene *scene, int ret)
{
	if (scene)
	{
		if (scene->camera)
			free(scene->camera);
		if (scene->ambient)
			free(scene->ambient);
		if (scene->mlx)
			free(scene->mlx);
		free(scene);
	}
	return (ret);
}

int	key_hook(int keycode, t_scene *scene)
{
	if (keycode == MAIN_PAD_ESC)
	{
		mlx_destroy_image(scene->mlx, scene->img.img);
		mlx_destroy_window(scene->mlx, scene->win);
		free_scene(scene, 0);
		exit(0);
	}
	return (0);
}

int	close_x(t_scene *scene)
{
	mlx_destroy_image(scene->mlx, scene->img.img);
	mlx_destroy_window(scene->mlx, scene->win);
	free_scene(scene, 0);
	exit(0);
}
