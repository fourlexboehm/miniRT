/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgobbett <jgobbett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 14:40:55 by aboehm            #+#    #+#             */
/*   Updated: 2022/09/19 14:17:20 by jgobbett         ###   ########.fr       */
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
# define DEGREE_TO_RAD(x) (x * M_PI / 180)

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

typedef struct s_vector3
{
	double	x;
	double	y;
	double	z;
}	t_vector3;

typedef struct s_ray
{
	t_vector3	O;
	t_vector3	D;
	t_rgba		colour;
	double		t;
	t_vector3	hitO;
	t_vector3	hitD;
	t_rgba		hitColour;
} t_ray;

typedef struct s_corners
{
	t_vector3	tl;
	t_vector3	tr;
	t_vector3	bl;
	t_vector3	br;
}	t_corners;

// -------------------------- objs ------------------

typedef	struct s_ambient_light
{
	double		ambient;
	t_rgba		colour;
}	t_ambient_light;

typedef	struct s_camera
{
	t_vector3	pos;
	t_vector3	rot;
	double		fov;
}	t_camera;

typedef	struct s_L
{
	t_vector3	pos;
	double		brightness;
	t_rgba		colour;
}	t_L;

typedef	struct s_pl
{
	t_vector3	pos;
	t_vector3	rot;
	t_rgba		colour;
}	t_pl;

typedef	struct s_cy
{
	t_vector3	pos;
	t_vector3	rot;
	double		diameter;
	double		height;
	t_rgba		colour;
}	t_cy;

typedef	struct s_sp
{
	t_vector3	pos;
	double		diameter;
	t_rgba		colour;
}	t_sp;

// -------------------------- end objs ------------------

//contains an array of objs, a camera and lights
typedef struct s_scene
{
	t_ambient_light	ambient_light;
	t_camera		camera;
	t_sp	*spheres;
	t_cy	*cylinders;
	t_pl	*planes;
	t_L		*lights;
	int		n_spheres;
	int		n_cylinders;
	int		n_planes;
	int		n_lights;
}	t_scene;

typedef struct s_all
{
	void	*mlx;
	void	*win;
	t_image	img;
	t_scene	scene;
}	t_all;

//viewport
t_vector3	**calculate_viewport_vectors(t_camera cam);

t_vector3	**set_cam_vectors(t_corners corn);

//mlx
void		render_image_on_mlx(int	**matrix_colours);
//utils
double		ft_atof(const char *str);

//parser
void		assign_scene(t_scene *scene, char **line);
void		assign_plane(t_scene *scene, char *line);
void		assign_light(t_scene *scene, char *line);
void		assign_cylinder(t_scene *scene, char *line);
void		assign_sphere(t_scene *scene, char *line);
void		get_n_obs(char **line, t_scene *scene);
void		next_num(char *line, int *j);
void		set_vector3(t_vector3 *vec, char *line, int *j);
char		**get_file(char *path);

//	------------------------------ vector ------------------------

t_vector3	scale_vector3(const t_vector3 vec, const double scale);
t_vector3	add_vector3(const t_vector3 v1, const t_vector3 v2);
t_vector3	subtract_vector3(const t_vector3 v1, const t_vector3 v2);
void		multi_vector3(t_vector3 *v1, t_vector3 *v2);
t_vector3	div_vector3(const t_vector3 vec, const double scale);
void		init_vec3(t_vector3 *v, double x, double y, double z);
t_vector3 	at(t_ray* ray, double t);
t_vector3 	unit_vector3(t_vector3 v1);
double		dot(t_vector3 v1, t_vector3 v2);
double		length_squared(t_vector3 const v3);
double		length(t_vector3 const v3);
t_vector3	new_vector3(double x, double y, double z);
double		get_distance_vector3(t_vector3 *v1, t_vector3 *v2);
double 		get_coord_rad_vector3(t_vector3 v1, t_vector3 v2);
double		get_coord_deg_vector3(t_vector3 *v1, t_vector3 *v2);
t_vector3	reflect(t_vector3 v, t_vector3 n);

//	------------------------------ colliders ------------------------

double		collide_sphere(t_ray* r, t_sp* s);
double		collide_plane(t_ray *r, t_pl *pl);

// -------------------------- ray ------------------------
void	ray_colour(t_ray *r, t_scene *s);

// -------------------------- colour------------------------
int	**set_colour_matrix(t_vector3 **v_matrix, t_scene scene);

#endif

// z is up and down