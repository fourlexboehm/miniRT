#include "minirt.h"

double	collide_sphere(t_ray *r, t_sp	*s)
{
	t_vector3	oc;
	double		a;
	double		b;
	double		c;
	double		discriminant;

	oc = subtract_vector3(r->O, s->pos);
	a = length_squared(r->D);
	b = dot(oc, r->D);
	c = length_squared(oc) - s->diameter * s->diameter;
	discriminant = (b * b) - (a * c);
	if (discriminant < 0)
		return (DBL_MAX);
	return ((-b - sqrt(discriminant)) / a);
}
