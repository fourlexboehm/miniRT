#ifndef PARSER_H
#define PARSER_H

# include <stdint.h>
# include <pthread.h>
# include <math.h>
# include <float.h>
# include <stdio.h>
#include <stdlib.h>

typedef struct s_rgba
{
	uint8_t		r;
	uint8_t		b;
	uint8_t		g;
}					t_rgba;

typedef struct s_vec
{
	double	x;
	double	y;
	double	z;
}	t_vec;


// -------------------------- objs ------------------

typedef	struct s_ambient_light
{
	double		ambient;
	t_rgba		colour;
}	t_ambient_light;

typedef	struct s_camera
{
	t_vec	pos;
	t_vec	dir;
	double		fov;
}	t_camera;

typedef	struct s_L
{
	t_vec	pos;
	double		brightness;
	t_rgba		colour;
}	t_L;

typedef	struct s_pl
{
	t_vec	pos;
	t_vec	dir;
	t_rgba		colour;
}	t_pl;

typedef	struct s_cy
{
	t_vec	pos;
	t_vec	dir;
	double		diameter;
	double		height;
	t_rgba		colour;
}	t_cy;

typedef	struct s_sp
{
	t_vec	pos;
	double		diameter;
	t_rgba		colour;
}	t_sp;

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

int get_double(char *str, double *d);
int get_rgba(char *str, t_rgba *rgba);
int get_vector(char *str, t_vec *vec);
int ft_isspace(char c);
int check_line(char *str, int num);
int num_count(char *str);

#endif