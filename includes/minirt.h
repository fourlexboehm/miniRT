/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgobbett <jgobbett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 14:40:55 by aboehm            #+#    #+#             */
/*   Updated: 2022/06/20 17:36:37 by jgobbett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "../libft/libft.h"
# include <stdint.h>
# include <pthread.h>

# define WIN_WIDTH 1280
# define WIN_HEIGHT 720
# define ZOOM 1.1f
# define THREADS 8

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
} t_vector3;

// --------------------------objs------------------

typedef	struct s_ambient_light
{
	double		ambient;
	t_rgba		color;
}	t_ambient_light;

typedef	struct s_camera
{
	double		pos_x;
	double		pos_y;
	double		pos_z;

	double		rot_x;
	double		rot_y;
	double		rot_z;
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
	t_vector3	rot;
	double		diameter;
	t_rgba		color;
}	t_sp;

// --------------------------objs------------------

typedef union
{
	t_sp	sphere;
	t_cy	cylinder;
	t_pl	plane;
} t_obj;

//contains an array of objs, a camera and lights
typedef struct s_scene
{
	t_ambient_light	light;
	t_camera		*camera;
	t_obj			*obj;

} t_scene;

typedef struct s_all
{

} t_all;

#endif
