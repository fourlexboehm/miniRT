#include "../includes/minirt.h"

t_vector3	reflect(t_vector3 v, t_vector3 n)
{
	return (subtract_vector3(v, scale_vector3(n, 2 * dot(v, n))));
}

void	check_collide(t_ray *r, t_scene *s)
{
	int		i;
	double	t;

	r->t = DBL_MAX;
	i = -1;
	while (++i < s->n_spheres)
	{
		t = collide_sphere(r, &s->spheres[i]);
		if (t < r->t)
		{
			r->t = t;
			r->colour = s->spheres[i].colour;
		}
	}
	i = -1;
	while (++i < s->n_planes)
	{
		t = collide_plane(r, &s->planes[i]);
		if (t < r->t)
		{
			r->t = t;
			r->colour = s->planes[i].colour;
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
            r->colour = s->cylinders[i].colour;
        }
    }
	*/
}

void	get_light(t_ray *r, t_scene *s)
{
	int	i;

	r->O = at(r, r->t);
	i = -1;
	while (++i < s->n_lights)
	{
		r->D = unit_vector3(subtract_vector3(r->O, s->lights[i].pos));
		check_collide(r, s);
		if (r->t < get_distance_vector3(&r->O, &s->lights[i].pos))
		{
			r->colour.r /= 2;
			r->colour.g /= 2;
			r->colour.b /= 2;
		}
	}
}

void	ray_colour(t_ray *r, t_scene *s)
{
	check_collide(r, s);
	if (r->t == DBL_MAX)
		r->colour = s->ambient_light.colour;
	else
		get_light(r, s);
}
