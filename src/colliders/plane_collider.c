#include "../../includes/minirt.h"

// double	plane_collider(t_ray *r, t_pl *pl)
// {
// 	double	d;

// 	d = dot(unit_vec(r->dir), pl->dir);
// 	if (d > 0)
// 	{
// 		return (dot(sub_vec(pl->pos, r->pos), pl->dir) / d);
// 	}
// 	return (DBL_MAX);
// }

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