#include "../includes/minirt.h"

double collide_sphere(t_ray* r, t_sp* s)
{
	t_vector3 oc = subtract_vector3(r->O, s->pos);
	double a = length_squared(r->D);
	double b = dot(oc, r->D);
	double c = length_squared(oc) - s->diameter * s->diameter;
	double discriminant = (b * b) - (a * c);
	if (discriminant < 0)
		return (DBL_MAX);
	return ((-b - sqrt(discriminant)) / a);
}