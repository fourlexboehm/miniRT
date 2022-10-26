/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_collider.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgobbett <jgobbett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 15:35:36 by jgobbett          #+#    #+#             */
/*   Updated: 2022/10/26 12:45:23 by jgobbett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"
#include <math.h>

double	solve_plane(t_vec o, t_vec d, t_vec plane_p, t_vec plane_nv)
{
	double	x;
	double	denom;

	denom = dot(plane_nv, d);
	if (denom == 0)
		return (INFINITY);
	x = (dot(plane_nv, sub_vec(plane_p, o))) / denom;
	if (x > 1e-4)
		return (x);
	else
		return (INFINITY);
}

static double	caps_intersection(t_ray ray, const t_cy cylinder)
{
	double	id1;
	double	id2;
	t_vec	ip1;
	t_vec	ip2;
	t_vec	c2;

	c2 = add_vec(cylinder.pos, scale_vec(cylinder.dir, cylinder.height));
	id1 = solve_plane(ray.pos, ray.dir, cylinder.pos, cylinder.dir);
	id2 = solve_plane(ray.pos, ray.dir, c2, cylinder.dir);
	if (id1 < INFINITY || id2 < INFINITY)
	{
		ip1 = add_vec(ray.pos, scale_vec(ray.dir, id1));
		ip2 = add_vec(ray.pos, scale_vec(ray.dir, id2));
		if ((id1 < INFINITY && get_distance(ip1, cylinder.pos)
				<= cylinder.radius2) && (id2 < INFINITY
				&& get_distance(ip2, c2) <= cylinder.radius2))
			return (min(id1, id2));
		else if (id1 < INFINITY && get_distance(
				ip1, cylinder.pos) <= cylinder.radius2)
			return (id1);
		else if (id2 < INFINITY && get_distance(ip2, c2) <= cylinder.radius2)
			return (id2);
	}
	return (INFINITY);
}

static bool	solve_cylinder(double x[2], t_ray ray, const t_cy cylinder)
{
	t_vec	v;
	t_vec	u;
	double	a;
	double	b;
	double	c;

	v = scale_vec(cylinder.dir, dot(ray.dir, cylinder.dir));
	v = sub_vec(ray.dir, v);
	u = scale_vec(cylinder.dir, dot(sub_vec(ray.pos,
					cylinder.pos), cylinder.dir));
	u = sub_vec(sub_vec(ray.pos, cylinder.pos), u);
	a = dot(v, v);
	b = 2 * dot(v, u);
	c = dot(u, u) - pow(cylinder.diameter * cylinder.diameter, 2);
	x[0] = (-b + sqrt(pow(b, 2) - 4 * a * c)) / (2 * a);
	x[1] = (-b - sqrt(pow(b, 2) - 4 * a * c)) / (2 * a);
	if (x[0] < 1e-4 && x[1] < 1e-4)
		return (0);
	return (1);
}

static double	cy_intersection(t_ray ray, const t_cy cylinder)
{
	double	x2[2];
	double	dist1;
	double	dist2;

	if (!solve_cylinder(x2, ray, cylinder))
		return (INFINITY);
	dist1 = dot(cylinder.dir, sub_vec
			(scale_vec(ray.dir, x2[0]), sub_vec(cylinder.pos, ray.pos)));
	dist2 = dot(cylinder.dir, sub_vec
			(scale_vec(ray.dir, x2[1]), sub_vec(cylinder.pos, ray.pos)));
	if (!((dist1 >= 0 && dist1 <= cylinder.height && x2[0] > 1e-4)
			|| (dist2 >= 0 && dist2 <= cylinder.height && x2[0] > 1e-4)))
		return (INFINITY);
	return (x2[0]);
}

double	cylinder_intersection(const t_ray ray
		, const t_cy cylinder, bool *is_on_side)
{
	double	cylinder_inter;
	double	caps_inter;

	cylinder_inter = cy_intersection(ray, cylinder);
	caps_inter = caps_intersection(ray, cylinder);
	if (cylinder_inter < DBL_MAX || caps_inter < DBL_MAX)
	{
		if (cylinder_inter < caps_inter)
		{
			*is_on_side = true;
			return (cylinder_inter);
		}
		return (caps_inter);
	}
	return (DBL_MAX);
}
