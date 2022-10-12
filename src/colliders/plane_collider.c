#include "../../includes/minirt.h"

double	plane_collider(t_ray *r, t_pl *pl)
{
	double	d;

	d = dot(unit_vec(r->dir), pl->dir);
	if (fabs(d) > 0)
	{
		return (dot(sub_vec(pl->pos, r->pos), pl->dir) / d);
	}
	return (DBL_MAX);
}
