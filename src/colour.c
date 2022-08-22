#include "../includes/minirt.h"
//TODO add T as argument?
static int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

/**
 * * Returns colour matrix malloced with a background colour set
*/
static int	**create_colour_matrix(void)
{
	int		i;
	int		**c_matrix;

	c_matrix = ft_calloc(sizeof(t_ray *), WIN_HEIGHT + 1);
	i = -1;
	while (++i < WIN_HEIGHT)
	{
		c_matrix[i] = ft_calloc(sizeof(t_ray), WIN_WIDTH + 1);
	}
	return (c_matrix);
}

/*
*	In this function, we're creating a matrix to store the colour of each pixel
*	in rgb (transformed to an int).
*/
int	**set_colour_matrix(t_vector3 **v_matrix, t_scene scene)
{
	int				x;
	int				y;
	int				**c_matrix;
	t_ray			r;

	y = -1;
	c_matrix = create_colour_matrix();
	while (++y < WIN_HEIGHT)
	{
		x = -1;
		while (++x < WIN_WIDTH)
		{
			r.D = v_matrix[y][x];
			r.O = scene.camera.pos;
			r.t = DBL_MAX;
			ray_colour(&r, &scene);
			c_matrix[y][x] = create_trgb(r.t, r.colour.r, r.colour.g, r.colour.b);
		}
	}
	free2d_array((void **) v_matrix);
	return (c_matrix);
}
