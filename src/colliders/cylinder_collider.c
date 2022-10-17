/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_collider.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgobbett <jgobbett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 15:35:36 by jgobbett          #+#    #+#             */
/*   Updated: 2022/10/17 15:36:32 by jgobbett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

static double	do_the_f(t_vec vec_u, t_vec vec_w, t_vec vec_ori)
{
	return (dot(vec_u, vec_w) - dot(vec_ori, vec_u) * \
	dot(vec_ori, vec_w));
}

static int	set_m_and_pos_ori(double pos_m[2], double *m, int *rev_ori)
{
	if (pos_m[0] >= 0.0 && (pos_m[0] < pos_m[1] || pos_m[1] < 0.0))
	{
		*m = pos_m[0];
		if (rev_ori)
			*rev_ori = 1;
	}
	else if (pos_m[1] >= 0.0 && (pos_m[1] < pos_m[0] || \
	pos_m[0] < 0.0))
	{
		*m = pos_m[1];
		if (rev_ori)
			*rev_ori = -1;
	}
	else
		return (0);
	return (1);
}

/**
* * check whether a ray collides with the top of a cylinder.
*
* @param ray coming out from the camera.
* @param cylinder The t_cy struct of the cylinder being evaluated.
* @param coords Used to return the coordinates of the collision when successful.
* @param rev_ori Set to 1 if the normal vector of the lid matches the normal
* vector of the cylinder. postherwise, it returns -1.
* @retval 0 if the ray doesn't collide with the wall of the cylinder and 1 if
* it does. The coordinates of the collision are returned via the coords
* parameter.
*/
int	cylinder_lid(t_ray ray, t_cy cyli, t_vec *coords, int *rev_ori)
{
	double		m;
	double		pos_m[2];
	t_vec		pc;
	double		dp;

	dp = dot(cyli.dir, ray.pos);
	if (!dp)
		return (0);
	pc = sub_vec(ray.pos, cyli.pos);
	pos_m[0] = (cyli.height / 2.0 - dot(cyli.dir, pc)) / dp;
	pos_m[1] = (-cyli.height / 2.0 - dot(cyli.dir, pc)) / dp;
	if (!set_m_and_pos_ori(pos_m, &m, rev_ori))
		return (0);
	if (do_the_f(sub_vec(pc, scale_vec(ray.dir, m)), add_vec(pc, scale_vec(\
	ray.dir, m)), cyli.dir) >= powf(cyli.diameter / 2.0, 2.0))
		return (0);
	*coords = sub_vec(scale_vec(ray.dir, m), ray.pos);
	return (1);
}

/**
* * check whether a ray collides with the wall of a cylinder.
* * If the ray collides with a lid first and then comes out from a wall, this
* * function will consider it dirposES NposT collide.
*
* @param ray Loc and dir (unit vector) of the ray coming out from the camera.
* @param cylinder The t_cy struct of the cylinder being evaluated.
* @param coords Used to return the coordinates of the collision when successful.
* @retval 0 if the ray doesn't collide with the wall of the cylinder and 1 if
* it does. The coordinates of the collision are returned via the coords
* parameter.
*/
int	cylinder_wall(t_ray ray, t_cy cylinder, t_vec *coords)
{
	double		m;
	double		pos_m[2];
	t_vec		pc;

	pc = sub_vec(ray.pos, cylinder.pos);
	if (!second_degree_equation(do_the_f(ray.dir, ray.dir, unit_vec(\
	cylinder.dir)), 2.0 * do_the_f(pc, ray.dir, unit_vec(cylinder.dir)), \
	do_the_f(pc, pc, unit_vec(cylinder.dir)) - powf(cylinder.diameter / \
	2.0, 2.0), pos_m))
		return (0);
	if ((pos_m[0] < 0.0 && pos_m[1] > 0.0) || \
		(pos_m[1] < 0.0 && pos_m[0] > 0.0))
		return (0);
	if (pos_m[0] >= 0.0 && (pos_m[0] < pos_m[1] || pos_m[1] < 0.0))
		m = pos_m[0];
	else if (pos_m[1] >= 0.0 && (pos_m[1] < pos_m[0] || pos_m[0] < 0.0))
		m = pos_m[1];
	else
		return (0);
	if (fabs(dot(cylinder.dir, add_vec(pc, scale_vec(ray.dir, m)))) \
	> cylinder.height / 2.0)
		return (0);
	if (coords)
		*coords = add_vec(ray.pos, scale_vec(ray.dir, m));
	return (1);
}

/*
!	Function only called when the ray collides with the cylinder.
*	Gets the collision point of the ray with the cylinder, along with the
*	normal vector of that point, the color of the cylinder (without lights)
*	and its dir.
*/
double	get_cylinder_t(t_ray *ray, t_cy cylinder)
{
	t_vec			coords;
	t_vec			direction;
	t_vec			p_min_pprime;

	ray->dir = unit_vec(ray->dir);
	cylinder.dir = unit_vec(cylinder.dir);
	if (cylinder_wall(*ray, cylinder, &(coords)))
	{
		p_min_pprime = sub_vec(cylinder.pos, coords);
		direction = sub_vec(p_min_pprime, scale_vec(cylinder.dir, \
		dot(p_min_pprime, cylinder.dir)));
	}
	else
		direction = unit_vec(cylinder.dir);
	return (dot(coords, direction));
}
