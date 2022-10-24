/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane_collider.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgobbett <jgobbett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 15:41:29 by jgobbett          #+#    #+#             */
/*   Updated: 2022/10/24 18:13:29 by jgobbett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

double	plane_collider(t_ray *r, t_pl *pl)
{
	double	t;
	double	d;

	d = dot(unit_vec(r->dir), pl->dir);
	t = dot(sub_vec(pl->pos, r->pos), pl->dir) / d;
	if (d > 0)
		return (t);
	return (DBL_MAX);
}

/*
double			solve_plane(t_vect o, t_vect d, t_vect plane_p, t_vect plane_nv)
{
	double	x;
	double	denom;

	denom = dot_product(plane_nv, d);
	if (denom == 0)
		return (INFINITY);
	x = (dot_product(plane_nv, sub_vect(plane_p, o))) / denom;
	return (x > EPSILON ? x : INFINITY);
}
*/