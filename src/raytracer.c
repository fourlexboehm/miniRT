#include "../includes/minirt.h"

t_vector3	reflect(t_vector3 v, t_vector3 n)
{
	return (subtract_vector3(v, scale_vector3(n, 2 * dot(v, n))));
}

double getAngle(t_vector3 a, t_vector3 b)
{
	return (acos( dot(a, b) / ((sqrt( a.x * a.x + a.y * a.y + a.z * a.z ) + 0.0000001) * ( sqrt( b.x * b.x + b.y * b.y + b.z * b.z ) + 0.0000001))));
}

void	check_collide(t_ray *r, t_scene *s, void *exempt)
{
	int		i;
	double	t;

	r->t = DBL_MAX;
	i = -1;
	while (++i < s->n_spheres)
	{
		// if (exempt != NULL)
		// 	printf("exempt =	%p\n sphere =	%p\n", exempt, &s->spheres[i]);
		if (&s->spheres[i] != exempt)
		{
			t = collide_sphere(r, &s->spheres[i]);
			if (t < r->t)
			{
				r->t = t;
				r->colour = s->spheres[i].colour;
				r->hitO = at(r, t);
				r->hitD = unit_vector3(reflect(r->D, unit_vector3(subtract_vector3(r->O, s->spheres[i].pos))));
				r->hitObject = &s->spheres[i];
			}
		}
	}
	i = -1;
	while (++i < s->n_planes)
	{
		if (&s->planes[i] != exempt)
		{
			t = collide_plane(r, &s->planes[i]);
			if (t < r->t)
			{
				r->t = t;
				r->hitO = at(r, t);
				r->hitD = scale_vector3(unit_vector3(reflect(s->planes->rot, r->D)), 1);
				r->colour = s->planes[i].colour;
			}
		}
	}
	i = -1;
    while (++i < s->n_cylinders)
    {
        t = collide_cylinder(*r, s->cylinders[i]);
        if (t < r->t)
        {
            r->t = t;
            r->colour = s->cylinders[i].colour;
        }
    }


	if ((t < s->last_t && t < DBL_MAX) || s->last_t == 0)
	{
		s->last_t = t;
		s->last_ray = *r;
	}
}

void	light_color(t_rgba *colour, double scalar)
{
	int	r;
	int	g;
	int b;

	r = colour->r + scalar;
	g = colour->g + scalar;
	b = colour->b + scalar;
	if (r > 255)
		colour->r = 255;
	else if (r < 0)
		colour->r = 0;
	else
		colour->r = r;
	
	
	if (g > 255)
		colour->g = 255;
	else if (g < 0)
		colour->g = 0;
	else
		colour->g = g;

	if (b > 255)
		colour->b = 255;
	else if (b < 0)
		colour->b = 0;
	else
		colour->b = b;
}

void	scale_color(t_rgba *colour, double scalar)
{
	int	r;
	int	g;
	int b;

	r = colour->r * scalar;
	g = colour->g * scalar;
	b = colour->b * scalar;
	if (r > 255)
		colour->r = 255;
	else if (r < 0)
		colour->r = 0;
	else
		colour->r = r;
	
	
	if (g > 255)
		colour->g = 255;
	else if (g < 0)
		colour->g = 0;
	else
		colour->g = g;

	if (b > 255)
		colour->b = 255;
	else if (b < 0)
		colour->b = 0;
	else
		colour->b = b;
}

void	get_light(t_ray *r, t_scene *s)
{
	int	i;
	t_ray light_ray;
	double	light_dis;

	if (s->n_lights == 0)
	{
		r->hitColour.r = 0;
		r->hitColour.g = 0;
		r->hitColour.b = 0;
		return ;
	}
	i = -1;
	while (++i < s->n_lights)
	{
		light_ray.O = r->hitO;
		light_ray.D = unit_vector3(subtract_vector3(r->hitO, s->lights[i].pos));

		check_collide(&light_ray, s, r->hitObject);
		light_dis = get_distance_vector3(s->lights[i].pos, light_ray.O);
		// if (light_ray.t != DBL_MAX)
		// 	printf("Light t		= %lf | light dis	= %lf\n",light_ray.t, light_dis);
		if (light_ray.t > 0 )//>= light_dis - 10 )
		{
			//double angle = getAngle(s->lights[i].pos, r->hitO) - getAngle(r->hitD, r->hitO);
			double angle = getAngle(s->lights[i].pos, r->hitO) - getAngle(r->hitD, r->hitO);
			double result = ((angle * -180) - get_distance_vector3(s->lights[i].pos, r->hitO)) * ((s->lights[i].brightness * 1) + .5);
			light_color(&r->hitColour, result * 1);
		}
		// else
		// 	light_color(&r->hitColour, -255);
	}
}

t_rgba addColour(t_rgba ColourA, t_rgba ColourB)
{
	t_rgba new;
	int	r;
	int	g;
	int	b;

	// new.r = (ColourA.r * .5) + (ColourB.r * .5);
	// new.g = (ColourA.g * .5) + (ColourB.g * .5);
	// new.b = (ColourA.b * .5) + (ColourB.b * .5);

	r = (ColourA.r * .75) + (ColourB.r * .75);
	g = (ColourA.g * .75) + (ColourB.g * .75);
	b = (ColourA.b * .75) + (ColourB.b * .75);

	if (r > 255)
		r = 255;
	if (g > 255)
		g = 255;
	if (b > 255)
		b = 255;

	new.r = r;
	new.g = g;
	new.b = b;
	return (new);
}

void	ray_colour(t_ray *r, t_scene *s)
{
	r->hitObject = NULL;
	check_collide(r, s, NULL);
	r->hitColour = r->colour;
	if (r->t == DBL_MAX)
	{
		r->colour.r = 0;
		r->colour.g = 0;
		r->colour.b = 0;
		scale_color(&r->colour, s->ambient_light.ambient);
	}
	else
	{
		scale_color(&r->colour, s->ambient_light.ambient);
		get_light(r, s);
		r->colour = addColour(r->colour, r->hitColour);
	}
}
