#include "../includes/minirt.h"

double collide_sphere(t_ray *r, t_sp *s)
{
	t_vector3 oc = subtract_vector3(r->O, s->pos);
	double a = length_squared(r->D);
	double b = dot(oc, r->D);
	double c = length_squared(oc) - s->diameter * s->diameter;
	double discriminant = (b * b) - (a * c);
	if (discriminant < 0)
		return (-1);
	else
		return ((-b - sqrt(discriminant)) / a);
}

double plane_collide(t_ray *r, t_pl *pl)
{
	double d;
	double t;

	t = 0;
	d = dot(unit_vector3(r->D), pl.rot);
	if (fabs(d) > 0)
		t = dot(subtract_vector3(pl.pos, r->O), pl.rot) / d;
	return (t);
}