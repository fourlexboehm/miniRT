#include "../../includes/minirt.h"

double	collide_plane(t_ray *r, t_pl *pl)
{
	double	d;

	d = dot(unit_vector3(r->D), pl->rot);
	if (fabs(d) > 0)
	{
		return (dot(subtract_vector3(pl->pos, r->O), pl->rot) / d);
	}
	return (DBL_MAX);
}
