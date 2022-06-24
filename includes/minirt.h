/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgobbett <jgobbett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 14:40:55 by aboehm            #+#    #+#             */
/*   Updated: 2022/06/24 15:04:59 by jgobbett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "../libft/libft.h"
# include "../miniLibX/mlx.h"
# include <stdint.h>
# include <pthread.h>

# define KEY_ESC 53
# define WIN_WIDTH 1280
# define WIN_HEIGHT 720
# define MLX_TITLE "MiniRT"

typedef struct s_rgba
{
	uint8_t		b;
	uint8_t		g;
	uint8_t		r;
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

// --------------------------objs------------------

typedef	struct s_ambient_light
{
	double		ambient;
	t_rgba		color;
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
	t_rgba		color;
}	t_L;

typedef	struct s_pl
{
	t_vector3	pos;
	t_vector3	rot;
	t_rgba		color;
}	t_pl;

typedef	struct s_cy
{
	t_vector3	pos;
	t_vector3	rot;
	double		diameter;
	double		height;
	t_rgba		color;
}	t_cy;

typedef	struct s_sp
{
	t_vector3	pos;
	double		diameter;
	t_rgba		color;
}	t_sp;

// --------------------------end objs------------------

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
	t_scene	scene;
}	t_all;

void	render_image_on_mlx(int	**matrix_colors);
double	ft_atof(const char *str);

//	------------------------------vector------------------------

void	add_vector3(t_vector3 *v1, t_vector3 *v2);
void	subtract_vector3(t_vector3 *v1, t_vector3 *v2);
void	multi_vector3(t_vector3 *v1, t_vector3 *v2);
void	scalar_vector3(t_vector3 *v1, double scalar);

double	get_distance_vector2(t_vector3 *v1, t_vector3 *v2);
double	get_distance_vector3(t_vector3 *v1, t_vector3 *v2);

double	get_coord_rad_vector3(t_vector3 *v1, t_vector3 *v2);
double	get_coord_deg_vector3(t_vector3 *v1, t_vector3 *v2);

#endif