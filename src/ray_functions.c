#include "../includes/minirt.h"

t_vector3 reflect(t_vector3 v, t_vector3 n)
{
	return subtract_vector3(v, scale_vector3(n, 2 * dot(v, n)));
}

t_vector3 get_reflect_color(t_vector3 v, t_vector3 n)
{
	t_ray ref;
	t_vector3 out_N;
	ref.O = at(r, t);

	out_N = unit_vector3(subtract_vector3(ref.O, sp.pos)); 

	ref.D = reflect(unit_vector3(r->D), out_N);

	t = collide_sphere_3D(&ref, &sp2);
	return subtract_vector3(v, scale_vector3(n, 2 * dot(v, n)));
}

void get_ray_color(t_ray *r, t_scene *s)
{
	int	i;
	double t;
	int	hit;

	i = -1;
	r->t = 9999999999;
	while (++i < s->n_spheres)
	{
		t = collide_sphere(r, &s->spheres[i]);
		if (t < r->t)
		{
			r->t = t;
			r->color = s->spheres[i].color;
			hit = 1;
		}
	}
	// i = -1;
	// while (++i < s->n_cylinders)
	// {
	// 	t = collide_sphere(r, &s->cylinders[i]);
	// 	if (t < r->t)
	// 	{
	// 		r->t = t;
	// 		r->color = s->cylinders[i].color;
	// 		hit = 1;
	// 	}
	// }
	i = -1;
	while (++i < s->n_planes)
	{
		t = collide_sphere(r, &s->planes[i]);
		if (t < r->t)
		{
			r->t = t;
			r->color = s->planes[i].color;
			hit = 1;
		}
	}
	if (hit)
		r->color = new_vector3(0, 0, 0); // ambiant light
}