/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_collider.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgobbett <jgobbett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 15:42:02 by jgobbett          #+#    #+#             */
/*   Updated: 2022/10/17 15:42:23 by jgobbett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

/**
 * returns t (distance) if it and returns BDL_MAX if nothing hit
 */
double	sphere_collider(t_ray *r, t_sp	*s)
{
	t_vec	oc;
	double	a;
	double	b;
	double	c;
	double	discriminant;

	oc = sub_vec(r->pos, s->pos);
	a = length_squared(r->dir);
	b = dot(oc, r->dir);
	c = length_squared(oc) - s->diameter * s->diameter;
	discriminant = (b * b) - (a * c);
	if (discriminant < 0)
		return (DBL_MAX);
	return ((-b - sqrt(discriminant)) / a);
}
