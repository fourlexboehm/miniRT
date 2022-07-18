#include "../includes/minirt.h"

int raytracer()
{

// Camera

}

t_vector3 reflect(t_vector3 v, t_vector3 n)
{
	return subtract_vector3(v, scale_vector3(n, 2 * dot(v, n)));
}

void ray_color(t_ray *r, t_scene *s)
{
	int    i;
    double t;

    r->t = DBL_MAX;
    i = -1;
    while (++i < s->n_spheres)
    {
        t = collide_sphere(r, &s->spheres[i]);
        if (t < r->t)
        {
            r->t = t;
            r->color = s->spheres[i].color;
        }
    }
	i = -1;
    while (++i < s->n_planes)
    {
        t = collide_plane(r, &s->planes[i]);
        if (t < r->t)
        {
            r->t = t;
            r->color = s->planes[i].color;
        }
    }
	/* WIP
	i = -1;
    while (++i < s->n_cylinders)
    {
        t = collide_cylinders(r, &s->cylinders[i]);
        if (t < r->t)
        {
            r->t = t;
            r->color = s->cylinders[i].color;
        }
    }
	*/
	if (r->t == DBL_MAX)
		r->color = s->ambient_light.color;
}
