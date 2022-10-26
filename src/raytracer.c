/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgobbett <jgobbett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 14:37:48 by jgobbett          #+#    #+#             */
/*   Updated: 2022/10/26 12:46:11 by jgobbett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

/**
 * works out the reflect angle between a direction and a normal
 */
t_vec	reflect_angle(t_vec v, t_vec n)
{
	return (sub_vec(v, scale_vec(n, 2 * dot(v, n))));
}

/**.
 * gets the angle between two vectores in rad
 **/
double	get_angle(t_vec a, t_vec b)
{
	return (acos(dot(a, b) / ((sqrt(a.x * a.x + a.y * a.y + a.z * a.z)
					+ 0.0000001) * (sqrt(b.x * b.x + b.y * b.y + b.z * b.z)
					+ 0.0000001))));
}

/**
 * gets light colour value including shadow
 * (original) gets light colour value including shadow
 */
void	get_light(t_ray *r, t_scene *s)
{
	int		i;
	t_ray	light_ray;
	double	angle;
	double	result;

	i = -1;
	while (++i < s->n_lights)
	{
		light_ray.pos = r->hit_pos;
		light_ray.dir = unit_vec(sub_vec(r->hit_pos, s->lights[i].pos));
		check_colliders(&light_ray, s, r->hit_object);
		if (light_ray.t > 0)
		{
			angle = get_angle(s->lights[i].pos, r->hit_pos)
				- get_angle(r->hit_dir, r->hit_pos);
			result = ((angle * -180) - get_distance(s->lights[i].pos,
						r->hit_pos)) * (-(s->lights[i].brightness - 1) + .5);
			r->hit_colour = light_rgba(color_mixer(r->hit_colour,
						s->lights[i].colour), result * 1);
		}
		else
			r->hit_colour = light_rgba(r->hit_colour, -255);
	}
}

/**
 * calculates the ray collider and configs 
 * the ray then calculates the lighting/colour
 */
void	ray_colour(t_ray *r, t_scene *s)
{
	r->hit_object = NULL;
	check_colliders(r, s, NULL);
	r->hit_colour = r->colour;
	if (r->t == DBL_MAX)
	{
		r->colour.r = 0;
		r->colour.g = 0;
		r->colour.b = 0;
		scale_rgba(&r->colour, s->ambient_light.ambient);
	}
	else
	{
		scale_rgba(&r->colour, s->ambient_light.ambient);
		get_light(r, s);
		r->colour = add_rgba(r->colour, r->hit_colour);
	}
}
