/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgobbett <jgobbett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 14:40:55 by aboehm            #+#    #+#             */
/*   Updated: 2022/10/24 18:34:39 by jgobbett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "../libft/libft.h"
# include "../miniLibX/mlx.h"
# include <stdint.h>
# include <pthread.h>
# include <math.h>
# include <float.h>

# define KEY_ESC 53
# define WIN_WIDTH 1280
# define WIN_HEIGHT 720
# define MLX_TITLE "MiniRT"

typedef struct s_rgba
{
	uint8_t		r;
	uint8_t		b;
	uint8_t		g;
}					t_rgba;

typedef struct s_image
{
	void		*image;
	char		*ptr;
	int			bpp;
	int			stride;
	int			endian;
}					t_image;

typedef struct s_vec
{
	double	x;
	double	y;
	double	z;
}	t_vec;

typedef struct s_ray
{
	t_vec	pos;
	t_vec	dir;
	t_rgba	colour;
	double	t;
	t_vec	hit_pos;
	t_vec	hit_dir;
	t_rgba	hit_colour;
	void	*hit_object;
}	t_ray;

typedef struct s_corners
{
	t_vec	tl;
	t_vec	tr;
	t_vec	bl;
	t_vec	br;
}	t_corners;

// -------------------------- objs ------------------

typedef struct s_ambient_light
{
	double	ambient;
	t_rgba	colour;
}	t_ambient_light;

typedef struct s_camera
{
	t_vec	pos;
	t_vec	dir;
	double	fov;
}	t_camera;

typedef struct s_L
{
	t_vec	pos;
	double	brightness;
	t_rgba	colour;
}	t_L;

typedef struct s_pl
{
	t_vec	pos;
	t_vec	dir;
	t_rgba	colour;
}	t_pl;

typedef struct s_cy
{
	t_vec	pos;
	t_vec	pos2;
	t_vec	dir;
	double	diameter;
	double	radius2;
	double	height;
	t_rgba	colour;
}	t_cy;

typedef struct s_sp
{
	t_vec	pos;
	double	diameter;
	t_rgba	colour;
}	t_sp;

// -------------------------- end objs ------------------

//contains an array of objs, a camera and lights
typedef struct s_scene
{
	t_ambient_light	ambient_light;
	t_camera		camera;
	t_sp			*spheres;
	t_cy			*cylinders;
	t_pl			*planes;
	t_L				*lights;
	int				n_spheres;
	int				n_cylinders;
	int				n_planes;
	int				n_lights;
	double			last_t;
	t_ray			last_ray;
}	t_scene;

typedef struct s_all
{
	void	*mlx;
	void	*win;
	t_image	img;
	t_scene	scene;
}	t_all;

//viewport
t_vec		**calculate_viewport_vectors(t_camera cam);

t_vec		**set_cam_vectors(t_corners corn);

//mlx
void		render_image_on_mlx(int	**matrix_colours);
//utils
double		ft_atof(const char *str);
int			second_degree_equation(double a, double b, double c, double d[2]);

//parser
int			is_inchar(char c);
int			get_double(char *str, double *d);
int			get_rgba(char *str, t_rgba *rgba);
int			get_vector(char *str, t_vec *vec);
int			check_line(char *str, int num);
int			assign_ambient_light(t_scene *scene, char *line);
int			num_count(char *str);
int			assign_camera(t_scene *scene, char *line);
int			assign_plane(t_scene *scene, char *line);
int			assign_cylinder(t_scene *scene, char *line);
int			assign_sphere(t_scene *scene, char *line);
void		get_n_obs(char **line, t_scene *scene);
void		next_num(char *line, int *j);
void		set_vec(t_vec *vec, char *line, int *j);
char		**get_file(char *path);

//	------------------------------ vector ------------------------

t_vec		scale_vec(t_vec vec, double scale);
t_vec		add_vec(t_vec v1, t_vec v2);
t_vec		sub_vec(t_vec v1, t_vec v2);
t_vec		reflect_angle(t_vec v, t_vec n);
t_vec		div_vec(t_vec vec, double scale);
t_vec		at(t_ray *ray, double t);
t_vec		unit_vec(t_vec v1);
t_vec		new_vec(double x, double y, double z);
void		multi_vec(t_vec *v1, t_vec *v2);
void		init_vec(t_vec *v, double x, double y, double z);
double		dot(t_vec v1, t_vec v2);
double		length_squared(t_vec v3);
double		length(t_vec v3);
double		get_distance(t_vec v1, t_vec v2);
double		get_coord_rad_vec(t_vec v1, t_vec v2);
double		get_coord_deg_vec(t_vec *v1, t_vec *v2);

//	------------------------------ colliders ------------------------

double		sphere_collider(t_ray *r, t_sp *s);
double		plane_collider(t_ray *r, t_pl *pl);
double		get_cylinder_t(t_ray *ray, t_cy cylinder);
void		check_colliders(t_ray *r, t_scene *s, void *exempt);

//	------------------------------ cylinder utils ------------------------

t_vec		get_closest_point_from_line(t_vec A, t_vec B, t_vec P);
double		cylinder_intersection(const t_ray ray,
				const t_cy cylinder, bool *is_on_side);

// -------------------------- ray ------------------------
void		ray_colour(t_ray *r, t_scene *s);

// -------------------------- colour------------------------
int			**set_colour_matrix(t_vec **v_matrix, t_scene scene);
t_rgba		add_rgba(t_rgba Colour_A, t_rgba Colour_B);
void		scale_rgba(t_rgba *colour, double scalar);
void		light_rgba(t_rgba *colour, double scalar);

#endif

// z is up and down