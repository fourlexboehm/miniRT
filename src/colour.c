#include "../includes/minirt.h"
//TODO add T as argument?

/**
 * creats a colour from int inputs.
 * no clamp, overflow not handled
 */
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

	c_matrix = ft_calloc(sizeof(t_ray *), WIN_WIDTH + 1);
	i = -1;
	while (++i < WIN_WIDTH)
	{
		c_matrix[i] = ft_calloc(sizeof(t_ray), WIN_HEIGHT + 1);
	}
	return (c_matrix);
}

/*
*	In this function, we're creating a matrix to store the colour of each pixel
*	in rgb (transformed to an int).
*/
int	**set_colour_matrix(t_vec **v_matrix, t_scene scene)
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
			r.dir = v_matrix[x][y];
			r.pos = scene.camera.pos;
			r.t = DBL_MAX;
			ray_colour(&r, &scene);
			c_matrix[x][y] = create_trgb(0, r.colour.r, r.colour.g, r.colour.b);
		}
	}
	t_ray *temp = &scene.last_ray;
	printf("last t was %lf\n", scene.last_t);
	printf("at	x:%lf	y:%lf	z:%lf\nsphere	x:%lf	y:%lf	z:%lf\n", at(temp, scene.last_t).x, at(temp, scene.last_t).y, at(temp, scene.last_t).z, scene.spheres[0].pos.x, scene.spheres[0].pos.y, scene.spheres[0].pos.z);
	printf("distance from cam to ball is %lf\n", get_distance(scene.spheres[0].pos, scene.last_ray.pos));
	printf("distance from 0,0,0 to 0,250,0 is %lf\n", get_distance(new_vec(0,0,0), new_vec(0,250,0)));
	printf("ray pos	x:%lf	y:%lf	z:%lf\n", temp->pos.x, temp->pos.y, temp->pos.z);
	free2d_array((void **) v_matrix);
	return (c_matrix);
}
