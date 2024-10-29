/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 14:08:04 by pmelis            #+#    #+#             */
/*   Updated: 2024/10/24 17:33:29 by pmelis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniHope.h"

int	file_extension_ok(char *scene)
{
	int	len;

	len = ft_strlen(scene);
	if (len < 3)
	{
		printf("Invalid .rt file extension: too short\n");
		return (1);
	}
	if (!((scene[len - 1] == 't') && (scene[len - 2] == 'r')
			&& (scene[len - 3] == '.')))
	{
		printf("Invalid .rt file extension\n");
		return (1);
	}
	return (0);
}

int	parse_scene(char *filename, t_scene *scene)
{
	int		fd;
	char	*line;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (perror_ret ("Error: Unable to open file\n"));
	line = NULL;
	line = get_next_line(fd);
	while (line)
	{
		if (check_ident(line, scene) != 0)
		{
			free(line);
			close(fd);
			return (1);
		}
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (0);
}

int	check_chars(char *line)
{
	int	i;

	i = 0;
	while (is_whitespace(line[i]))
		i++;
	if (!line[i])
		return (EMPTY);
	if (line[i] == '#')
		return (COMMENT);
	if (line[i] == 'A' && is_whitespace(line[i + 1]))
		return (A);
	if (line[i] == 'C' && is_whitespace(line[i + 1]))
		return (C);
	if (line[i] == 'L' && is_whitespace(line[i + 1]))
		return (L);
	if (line[i] == 'p' && line[i + 1] == 'l' && is_whitespace(line[i + 2]))
		return (PL);
	if (line[i] == 's' && line[i + 1] == 'p' && is_whitespace(line[i + 2]))
		return (SP);
	if (line[i] == 'c' && line[i + 1] == 'y' && is_whitespace(line[i + 2]))
		return (CY);
	return (INVALID);
}

t_scene	*init_scene(void)
{
	t_scene	*scene;
	int		i;

	scene = malloc(sizeof(t_scene));
	if (!scene)
	{
		perror("Error: Memory allocation failed for scene\n");
		exit(1);
	}
	scene->object_count = 0;
	scene->light_count = 0;
	scene->ambient = NULL;
	scene->camera = NULL;
	scene->width = 800;
	scene->height = 800;
	scene->anti_aliasing_samples = 4;
	scene->mlx = NULL;
	i = 0;
	while (i < MAX_LIGHTS)
	{
		scene->lights[i].position = (t_vec3){0, 0, 0};
		scene->lights[i].color = (t_vec3){0, 0, 0};
		scene->lights[i++].intensity = 0.0f;
	}
	return (scene);
}
