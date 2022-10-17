/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collider_fun.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgobbett <jgobbett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 14:49:43 by jgobbett          #+#    #+#             */
/*   Updated: 2022/10/17 15:28:30 by jgobbett         ###   ########.fr       */
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

void	cylinder_check(t_ray *r, t_scene *s, double *t)
{
	int	i;

	i = -1;
	while (++i < s->n_cylinders)
		*t = get_cylinder_t(r, s->cylinders[i]);
	if ((*t < s->last_t && *t < DBL_MAX) || s->last_t == 0)
	{
		r->t = *t;
		r->colour = s->spheres[i].colour;
		r->hit_pos = at(r, *t);
		r->hit_dir = unit_vec(reflect_angle(r->dir,
					unit_vec(sub_vec(r->pos, s->spheres[i].pos))));
		r->hit_object = &s->spheres[i];
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
	cylinder_check(r, s, &t);
	if ((t < s->last_t && t < DBL_MAX) || s->last_t == 0)
	{
		s->last_t = t;
		s->last_ray = *r;
	}
}
