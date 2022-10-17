/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   viewport.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgobbett <jgobbett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 15:45:34 by jgobbett          #+#    #+#             */
/*   Updated: 2022/10/17 15:45:50 by jgobbett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

/**
 * Normalize the vector to a unit vector
 */
static t_vec	vector_to_unit(t_vec v)
{
	t_vec	unit;
	double	mag;

	mag = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
	unit.x = v.x / mag;
	unit.y = v.y / mag;
	unit.z = v.z / mag;
	return (unit);
}

/**
 * converts the fov from degrees to radians, then calculate the
 * coordinates for each axis of each corner
 * @param fov		in degrees
 */
static t_corners	calculate_corners(t_vec unit_v, t_vec unit_q, \
t_vec a, double fov)
{
	t_corners	corn;
	double		ang_tan;
	t_vec		scaled_q;
	t_vec		scaled_v_x_tan;

	ang_tan = tanf((fov / 2.0) * M_PI / 180.0);
	scaled_v_x_tan = scale_vec(a, ang_tan * (9.0 / 16.0));
	scaled_q = scale_vec(unit_q, ang_tan);
	corn.tl = unit_vec(add_vec(sub_vec(unit_v, scaled_q), scaled_v_x_tan));
	corn.tr = unit_vec(add_vec(add_vec(unit_v, scaled_q), scaled_v_x_tan));
	corn.bl = unit_vec(sub_vec(sub_vec(unit_v, scaled_q),
				scaled_v_x_tan));
	corn.br = unit_vec(sub_vec(add_vec(unit_v, scaled_q), scaled_v_x_tan));
	return (corn);
}

static t_vec	get_unit_q(t_vec unit_v)
{
	t_vec	q;
	t_vec	unit_q;
	double	mag;

	q.x = -unit_v.z;
	q.y = 0.0;
	q.z = unit_v.x;
	mag = sqrt(q.x * q.x + q.y * q.y + q.z * q.z);
	if (mag)
	{
		unit_q.x = q.x / mag;
		unit_q.z = q.z / mag;
	}
	else
	{
		unit_q.x = 1.0;
		unit_q.z = 0.0;
	}
	unit_q.y = 0.0;
	return (unit_q);
}

t_vec	**calculate_viewport_vectors(t_camera cam)
{
	t_vec		unit_v;
	t_vec		unit_q;
	t_vec		a;
	t_corners	corners;

	unit_v = vector_to_unit(cam.dir);
	unit_q = get_unit_q(unit_v);
	a.x = -unit_q.z * unit_v.y;
	a.y = +unit_v.x * unit_q.z - unit_q.x * unit_v.z;
	a.z = unit_q.x * unit_v.y;
	corners = calculate_corners(unit_v, unit_q, a, cam.fov);
	return (set_cam_vectors(corners));
}
