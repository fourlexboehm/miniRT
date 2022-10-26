/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colour.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgobbett <jgobbett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 14:47:18 by jgobbett          #+#    #+#             */
/*   Updated: 2022/10/26 12:21:16 by jgobbett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	free2d_array((void **) v_matrix);
	return (c_matrix);
}

/**
 * multiplys the two colours by .75 and then adds 
 * them together then clamps the values to 0-255
 */
t_rgba	add_rgba(t_rgba Colour_A, t_rgba Colour_B)
{
	t_rgba	new;
	int		r;
	int		g;
	int		b;

	r = (Colour_A.r * .5) + (Colour_B.r * .5);
	g = (Colour_A.g * .5) + (Colour_B.g * .5);
	b = (Colour_A.b * .5) + (Colour_B.b * .5);
	if (r > 255)
		r = 255;
	if (g > 255)
		g = 255;
	if (b > 255)
		b = 255;
	new.r = r;
	new.g = g;
	new.b = b;
	return (new);
}

/**
 * scales rgba with multiplication by the scalar
 */
void	scale_rgba(t_rgba *colour, double scalar)
{
	int	r;
	int	g;
	int	b;

	r = colour->r * scalar;
	g = colour->g * scalar;
	b = colour->b * scalar;
	if (r > 255)
		colour->r = 255;
	else if (r < 0)
		colour->r = 0;
	else
		colour->r = r;
	if (g > 255)
		colour->g = 255;
	else if (g < 0)
		colour->g = 0;
	else
		colour->g = g;
	if (b > 255)
		colour->b = 255;
	else if (b < 0)
		colour->b = 0;
	else
		colour->b = b;
}
