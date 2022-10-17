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
	else if (cylinder_lid(*ray, cylinder, &(coords), &rev_ori))
		direction = unit_vec(scale_vec(cylinder.dir, rev_ori));

	t = get_distance(ray->pos, cylinder.pos);
	return (t);
}
//
//double			solve_plane(t_vec o, t_vec d, t_vec plane_p, t_vec plane_nv)
//{
//	double	x;
//	double	denom;
//
//	denom = dot(plane_nv, d);
//	if (denom == 0)
//		return (INFINITY);
//	x = (dot(plane_nv, sub_vec(plane_p, o))) / denom;
//	return (x > EPSILON ? x : INFINITY);
//}
//
//static double	caps_intersection(t_ray ray, const t_cy cylinder)
//{
//	double	id1;
//	double	id2;
//	t_vec	ip1;
//	t_vec	ip2;
//	t_vec	c2;
//
//	c2 = add_vec(cylinder.pos, scale_vec(cylinder.dir, cylinder.height));
//	id1 = solve_plane(ray.pos, ray.dir, cylinder.pos, cylinder.dir);
//	id2 = solve_plane(ray.pos, ray.dir, c2, cylinder.dir);
//	if (id1 < INFINITY || id2 < INFINITY)
//	{
//		ip1 = add_vec(ray.pos, scale_vec(ray.dir, id1));
//		ip2 = add_vec(ray.pos, scale_vec(ray.dir, id2));
//		if ((id1 < INFINITY && get_distance(ip1, cylinder.pos) <= cylinder.diameter * cylinder.diameter) && (id2 < INFINITY && get_distance(ip2, c2) <= cylinder.diameter * cylinder.diameter))
//			return (id1 < id2 ? id1 : id2);
//		else if (id1 < INFINITY && get_distance(ip1, cylinder.pos) <= cylinder.diameter * cylinder.diameter)
//			return (id1);
//		else if (id2 < INFINITY && get_distance(ip2, c2) <= cylinder.diameter * cylinder.diameter)
//			return (id2);
//	}
//	return (INFINITY);
//}
//
//static bool	solve_cylinder(double x[2], t_ray ray, const t_cy cylinder)
//{
//	t_vec	v;
//	t_vec	u;
//	double	a;
//	double	b;
//	double	c;
//
//	v = scale_vec(cylinder.dir, dot(ray.dir, cylinder.dir));
//	v = sub_vec(ray.dir, v);
//	u = scale_vec(cylinder.dir, dot(sub_vec(ray.pos, cylinder.pos), cylinder.dir));
//	u = sub_vec(sub_vec(ray.pos, cylinder.pos), u);
//	a = dot(v, v);
//	b = 2 * dot(v, u);
//	c = dot(u, u) - pow(cylinder.diameter * cylinder.diameter, 2);
//	x[0] = (-b + sqrt(pow(b, 2) - 4 * a * c)) / (2 * a);
//	x[1] = (-b - sqrt(pow(b, 2) - 4 * a * c)) / (2 * a);
//	if (x[0] < EPSILON && x[1] < EPSILON)
//		return (0);
//	return (1);
//}
//
//static void		calc_cy_normal(double x2[2], const t_cy cylinder, double dist1, double dist2)
//{
////	double	dist;
//	double	x;
//
//	if ((dist1 >= 0 && dist1 <= cylinder.height && x2[0] > EPSILON) && (dist2 >= 0 && dist2 <= cylinder.height && x2[1] > EPSILON))
//	{
//		x = x2[0] < x2[1] ? x2[0] : x2[1];
//	}
//	else if (dist1 >= 0 && dist1 <= cylinder.height && x2[0] > EPSILON)
//	{
//		x = x2[0];
//	}
//	else
//	{
//		x = x2[1];
//	}
//	x2[0] = x;
//}
//
//static double	cy_intersection(t_ray ray, const t_cy cylinder)
//{
//	double	x2[2];
//
//	if (!solve_cylinder(x2, ray, cylinder))
//		return (INFINITY);
//	double dist1 = dot(cylinder.dir, sub_vec(scale_vec(ray.dir, x2[0]), sub_vec(cylinder.pos, ray.pos)));
//	double dist2 = dot(cylinder.dir, sub_vec(scale_vec(ray.dir, x2[1]), sub_vec(cylinder.pos, ray.pos)));
//	if (!((dist1 >= 0 && dist1 <= cylinder.height && x2[0] > EPSILON) || (dist2 >= 0 && dist2 <= cylinder.height && x2[0] > EPSILON)))
//		return (INFINITY);
//	calc_cy_normal(x2, cylinder, dist1, dist2);
//	return (x2[0]);
//}
//
//double	cylinder_intersection(const t_ray ray, const t_cy cylinder, bool *is_on_side)
//double	get_cylinder_t(const t_ray ray, const t_cy cylinder, bool *is_on_side)
//{
//	double	cylinder_inter;
//	double	caps_inter;
//
//	cylinder_inter = cy_intersection(ray, cylinder);
//	if (!cylinder.is_closed)
//		caps_inter = INFINITY;
//	else
//		caps_inter = caps_intersection(ray, cylinder);
//	if (cylinder_inter < INFINITY || caps_inter < INFINITY)
//	{
//		if (cylinder_inter < caps_inter)
//		{
//			*is_on_side = true;
//			return (cylinder_inter);
//		}
//		return (caps_inter);
//	}
//	return (INFINITY);
//}
//
//t_vec get_closest_point_from_line(t_vec A, t_vec B, t_vec P)
//{
//	t_vec AP = sub_vec(P, A);
//	t_vec AB = sub_vec(B, A);
//	double ab2 = dot(AB, AB);
//	double ap_ab = dot(AP, AB);
//	double t = ap_ab / ab2;
//	if (t < 0.0)
//		t = 0.0;
//	else if (t > 1.0)
//		t = 1.0;
//	return (add_vec(A, scale_vec(AB, t)));
//}
//
//void	ray_cylinders(const t_ray ray, const t_scene *scene, t_impact *impact, void **object)
//{
//	t_list		*cylinders;
//	t_cy	*cylinder;
//	double		tmp;
//	bool		is_on_side;
//
//	cylinders = scene->cylinders;
//	while (cylinders->next)
//	{
//		is_on_side = false;
//		cylinder = (t_cy *)(cylinders->content);
//		if ((tmp = get_cylinder_t(ray, *cylinder, &is_on_side)) < impact->dist && tmp > 0)
//		{
//			*object = cylinder;
//			impact->dist = tmp;
//			impact->pos = new_vec(tmp * ray.dir.x, tmp * ray.dir.y, tmp * ray.dir.z);
//			if (is_on_side)
//				impact->normal = sub_vec(get_closest_point_from_line(cylinder->pos, cylinder->pos2, impact->pos), impact->pos);
//			else
//				impact->normal = cylinder->dir;
//			impact->normal = unit_vec(impact->normal);
//			impact->type = "cy";
//		}
//		cylinders = cylinders->next;
//	}
//}