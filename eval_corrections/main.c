/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grbuchne <grbuchne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 12:13:29 by pmelis            #+#    #+#             */
/*   Updated: 2024/10/28 21:17:05 by grbuchne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniHope.h"

int	print_usage(void)
{
	printf("Usage:\n");
	printf("option 1:\n");
	printf("./minirt <*.rt>\n\n");
	printf("option 2:\n");
	printf("./minirt <*.rt> <width> <height> <anti alias samples>\n\n");
	return (1);
}

int	check_acl_amount(t_scene *scene)
{
	if (scene->ambient == NULL)
		return (perror_ret("Error: Scene must have one ambient light\n"));
	if (scene->camera == NULL)
		return (perror_ret("Error: Scene must have one camera\n"));
	if (scene->light_count == 0)
		return (
			perror_ret("Error: Scene must have at least one light source\n"));
	return (0);
}

// Fix Nxyz (0,0,0) causes unexpected behaviour
int	main(int ac, char **av)
{
	t_scene	*scene;

	if (ac != 2 && ac != 5)
		return (print_usage());
	if (file_extension_ok(av[1]))
		return (1);
	scene = init_scene();
	if (ac == 5)
	{
		scene->width = ft_atoi(av[2]);
		scene->height = ft_atoi(av[3]);
		scene->anti_aliasing_samples = ft_atoi(av[4]);
	}
	if (parse_scene(av[1], scene) != 0)
		return (free_scene(scene, 1));
	if (check_acl_amount(scene) != 0)
		return (free_scene(scene, 1));
	print_scene(scene);
	render(scene);
	return (0);
}
