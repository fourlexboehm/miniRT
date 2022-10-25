/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collider_fun.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgobbett <jgobbett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 14:49:43 by jgobbett          #+#    #+#             */
/*   Updated: 2022/10/24 19:05:40 by jgobbett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void	sphere_check(t_ray *r, t_scene *s, void *exempt, double *t)
{
	int	i;

	i = -1;
	while (++i < s->n_spheres)
	{
		if (&s->spheres[i] != exempt)
		{
			*t = sphere_collider(r, &s->spheres[i]);
			if (*t < r->t)
			{
				r->t = *t;
				r->colour = s->spheres[i].colour;
				r->hit_pos = at(r, *t);
				r->hit_dir = unit_vec(reflect_angle(r->dir,
							unit_vec(sub_vec(r->pos, s->spheres[i].pos))));
				r->hit_object = &s->spheres[i];
			}
		}
	}
}

void	plane_check(t_ray *r, t_scene *s, void *exempt, double *t)
{
	int	i;

	i = -1;
	while (++i < s->n_planes)
	{
		if (&s->planes[i] != exempt)
		{
			*t = plane_collider(r, &s->planes[i]);
			if (*t < r->t)
			{
				r->t = *t;
				r->hit_pos = at(r, *t);
				r->hit_dir = scale_vec(
						unit_vec(reflect_angle(s->planes[i].dir, r->dir)), 1);
				r->colour = s->planes[i].colour;
				r->hit_object = &s->spheres[i];
			}
		}
	}
}

void	assign_ray(t_ray *r, t_cy *cy, double *t, bool ios)
{
	r->t = *t;
	r->hit_pos = scale_vec(r->dir, *t);
	if (ios)
		r->hit_dir = sub_vec(get_closest_point_from_line(
					cy->pos, cy->pos2,
					r->hit_pos), r->hit_pos);
	else
		r->hit_dir = cy->dir;
	r->hit_dir = unit_vec(r->hit_dir);
	r->hit_object = cy;
	r->colour = cy->colour;
}

void	cylinder_check(t_ray *r, t_scene *s, void *exempt, double *t)
{
	int		i;
	bool	is_on_side;

	i = -1;
	while (++i < s->n_cylinders)
	{
		if (&s->cylinders[i] != exempt)
		{
			is_on_side = false;
			*t = cylinder_intersection(*r, s->cylinders[i], &is_on_side);
			if (*t != DBL_MAX && *t > 0 && *t < r->t)
				assign_ray(r, &s->cylinders[i], t, is_on_side);
		}
	}
}

/**
 * goes though every collider and configs ray
 * with option to exempt an object
 **/
void	check_colliders(t_ray *r, t_scene *s, void *exempt)
{
	double	t;

	r->t = DBL_MAX;
	sphere_check(r, s, exempt, &t);
	plane_check(r, s, exempt, &t);
	cylinder_check(r, s, exempt, &t);
	if ((t < s->last_t && t < DBL_MAX) || s->last_t == 0)
	{
		s->last_t = t;
		s->last_ray = *r;
	}
}
