/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniHope.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmelis <pmelis@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 09:54:20 by pmelis            #+#    #+#             */
/*   Updated: 2024/10/24 18:08:34 by pmelis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIHOPE_H
# define MINIHOPE_H

# include <stdio.h> // printf, perror
# include <unistd.h> // write, close, read
# include <stdlib.h> // malloc, free, exit
# include <fcntl.h> // open
# include <math.h> // math library -> -lm flag needed (man 3 math)
// # include "./mlx/mlx.h"
// # include <sys/stat.h> // open
// # include <string.h> // strerror
# include <mlx.h> // minilibX

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1000
# endif

# define MAX_OBJECTS 100
# define MAX_LIGHTS 10

# define MAIN_PAD_ESC 65307
# define ON_DESTROY 17

# define M_PI 3.14159265358979323846

typedef struct s_vec3
{
	float	x;
	float	y;
	float	z;
}	t_vec3;

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

typedef enum e_object_type
{
	SPHERE,
	PLANE,
	CYLINDER
}	t_ObjectType;

typedef enum e_ident
{
	EMPTY = 0,
	A = 1,
	C = 2,
	L = 3,
	PL = 4,
	SP = 5,
	CY = 6,
	COMMENT = 7,
	INVALID = 8,
}	t_ident;

typedef struct s_object
{
	t_ObjectType	type;
	union
	{
		struct
		{
			t_vec3	center;
			float	radius;
		}	s_sphere;
		struct
		{
			t_vec3	point;
			t_vec3	normal;
		}	s_plane;
		struct
		{
			t_vec3	center;
			t_vec3	axis;
			float	radius;
			float	height;
			t_vec3	base_center;
		}	s_cylinder;
	};
	t_vec3			color;
}	t_object;

typedef struct s_ray
{
	t_vec3	origin;
	t_vec3	direction;
}	t_ray;

typedef struct s_light
{
	t_vec3	position;
	t_vec3	color;
	float	intensity;
}	t_light;

typedef struct s_ambient_light
{
	float	intensity;
	t_vec3	color;
}	t_ambient_light;

typedef struct s_camera
{
	t_vec3	position;
	t_vec3	direction;
	t_vec3	up;
	float	fov;
	float	aspect_ratio;
}	t_camera;

typedef struct s_scene
{
	int				object_count;
	t_object		objects[MAX_OBJECTS];
	int				light_count;
	t_light			lights[MAX_LIGHTS];
	t_camera		*camera;
	t_ambient_light	*ambient;
	int				width;
	int				height;
	int				anti_aliasing_samples;
	void			*mlx;
	void			*win;
	t_data			img;
}	t_scene;

typedef struct s_ray_ret
{
	t_vec3			unit_direction;
	float			t_background;
	t_vec3			white;
	t_vec3			blue;
	t_vec3			background_color;
}	t_ray_ret;

typedef struct s_ray_calc
{
	float	theta;
	float	half_height;
	float	half_width;
	t_vec3	w;
	t_vec3	u_axis;
	t_vec3	v_axis;
	t_vec3	lower_left_corner;
	t_vec3	horizontal;
	t_vec3	vertical;
	t_vec3	direction;
}	t_ray_calc;

typedef struct s_ray_color_calc
{
	float	closest_t;
	int		closest_object;
	float	t;
	int		i;
	t_vec3	hit_point;
	t_vec3	normal;
	t_vec3	color;
	t_vec3	light_dir;
	float	light_distance;
	float	diffuse;
	t_vec3	diffuse_color;
	float	max_component;

}	t_ray_color_calc;

// check_ident.c
void			comment_empty_case(int ident);
void			camera_setup(t_camera *camera, t_scene *scene);
int				acl_case(t_scene *scene, int ident, char *line);
int				check_ident(char *line, t_scene *scene);
// cleanup.c
int				perror_ret(char *msg);
int				free_scene(t_scene *scene, int ret);
int				key_hook(int keycode, t_scene *scene);
int				close_x(t_scene *scene);
// get_next_line.c
char			*get_next_line(int fd);
// get_utils.c
char			*get_next_value(char **str, char *delim);
int				set_rgb(t_vec3 *color, char **str);
int				set_nxyz(t_vec3 *dir, char **str);
int				set_xyz(t_vec3 *coor, char **str);
// getters_acl.c
int				get_a(char *line, t_scene *scene);
int				get_c(char *line, t_scene *scene);
int				get_l(char *line, t_scene *scene);
// getters.c
int				get_pl(char *line, t_scene *scene);
int				set_cylinder_attributes(t_object *obj, char **line);
int				get_cy(char *line, t_scene *scene);
int				get_sp(char *line, t_scene *scene);
// parse_tools.c
int				file_extension_ok(char *scene);
int				parse_scene(char *filename, t_scene *scene);
int				check_chars(char *line);
t_scene			*init_scene(void);
// mlx_extras.c
void			my_mlx_pixel_put(t_data *data, int x, int y, int color);
int				create_trgb( int r, int g, int b);
// print_lights.c
void			print_light(t_light *light);
void			print_ambient_light(t_ambient_light *ambient);
// print_objs.c
void			print_object(t_object *object);
void			sp_print(t_object *object);
void			pl_print(t_object *object);
void			cy_print(t_object *object);
// print.c
void			print_vec3(t_vec3 vec);
void			print_data(t_data *data);
void			print_ray(t_ray *ray);
void			print_camera(t_camera *camera);
void			print_scene(t_scene *scene);
// in_shadow.c
int				check_cylinder_intersection(t_ray shadow_ray, t_object object,
					float light_distance, float *t);
int				check_sphere_intersection(t_ray shadow_ray, t_object object,
					float light_distance, float *t);
int				check_plane_intersection(t_ray shadow_ray, t_object object,
					float light_distance, float *t);
int				is_in_shadow_loop(t_ray sr, t_scene *scene, float ld);
int				is_in_shadow(t_vec3 point, t_vec3 light_dir,
					float light_distance, t_scene *scene);
// ray_color.c
t_vec3			ray_color_ret(t_ray ray, t_scene *scene);
void			ray_color_loop2(t_scene *scene, t_ray_color_calc *calc);
t_vec3			closest_calc(t_scene *scene, t_ray_color_calc *calc,
					t_ray *ray);
void			ray_color_loop(t_scene *scene, t_ray *ray,
					t_ray_color_calc *calc);
t_vec3			ray_color(t_ray ray, t_scene *scene);
// ray_color_tools.c
t_ray			get_ray(float u, float v, t_camera camera);
void			set_closest(t_ray_color_calc *calc, int i);
// window_fill.c
void			fill_window(t_data img, t_scene *scene);
t_vec3			anti_alias_pixel(int i, int j, int samples, t_scene *scene);
int				t_calc(t_ray ray, t_object *obj, float *t0, float *t1);
float			y_calc(t_ray ray, t_object *obj, float t);
int				intersect_cylinder(t_ray ray, t_object *obj, float *t);
// render.c
int				intersect_sphere_2(float a, float b, float discriminant,
					float *t);
int				intersect_sphere(t_ray ray, t_vec3 center, float radius,
					float *t);
int				intersect_plane(t_ray ray, t_vec3 point, t_vec3 normal,
					float *t);
t_vec3			get_cylinder_normal(t_vec3 hit_point, t_object cylinder);
void			render(t_scene *scene);
// utils.c
int				ft_strlen(const char *str);
int				is_whitespace(char c);
int				ft_atoi(const char *str);
char			*ft_strchr(const char *s, int c);
char			*ft_strjoin(char *s1, char *s2);
// utils2.c
int				ft_set_atof(const char	*str, float *result_value);
char			*ft_strcpy(char *dest, const char *src);
// vector_ops.c
t_vec3			vec3_create(float x, float y, float z);
t_vec3			vec3_add(t_vec3 a, t_vec3 b);
t_vec3			vec3_subtract(t_vec3 a, t_vec3 b);
t_vec3			vec3_multiply(t_vec3 v, float s);
t_vec3			vec3_multiply_components(t_vec3 a, t_vec3 b);
// vector_ops2.c
float			vec3_dot(t_vec3 a, t_vec3 b);
float			vec3_length(t_vec3 v);
t_vec3			vec3_normalize(t_vec3 v);
t_vec3			vec3_cross(t_vec3 a, t_vec3 b);
void			normalize_colors(t_vec3 *colors);

#endif