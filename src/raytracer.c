#include "../includes/minirt.h"

/**
 * works out the reflect angle between a direction and a normal
 */
t_vec	reflect_angle(t_vec v, t_vec n)
{
	return (sub_vec(v, scale_vec(n, 2 * dot(v, n))));
}

/**
 * gets the angle between two vectores in rad
 **/
double get_angle(t_vec a, t_vec b)
{
	return (acos( dot(a, b) / ((sqrt( a.x * a.x + a.y * a.y + a.z * a.z ) + 0.0000001) * ( sqrt( b.x * b.x + b.y * b.y + b.z * b.z ) + 0.0000001))));
}

/**
 * goes though every collider and configs ray
 * with option to exempt an object
 **/
void	check_colliders(t_ray *r, t_scene *s, void *exempt)
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
			t = sphere_collider(r, &s->spheres[i]);
			if (t < r->t)
			{
				r->t = t;
				r->colour = s->spheres[i].colour;
				r->hit_pos = at(r, t);
				r->hit_dir = unit_vec(reflect_angle(r->dir, unit_vec(sub_vec(r->pos, s->spheres[i].pos))));
				r->hit_object = &s->spheres[i];
			}
		}
	}
	i = -1;
	while (++i < s->n_planes)
	{
		if (&s->planes[i] != exempt)
		{
			t = plane_collider(r, &s->planes[i]);
			if (t < r->t)
			{
				r->t = t;
				r->hit_pos = at(r, t);
				r->hit_dir = scale_vec(unit_vec(reflect_angle(s->planes->dir, r->dir)), 1);
				r->colour = s->planes[i].colour;
			}
		}
	}
	i = -1;
    while (++i < s->n_cylinders)
		t = get_cylinder_t(r, s->cylinders[i]);
	if ((t < s->last_t && t < DBL_MAX) || s->last_t == 0)
	{
		r->t = t;
		r->colour = s->spheres[i].colour;
		r->hit_pos = at(r, t);
		r->hit_dir = unit_vec(reflect_angle(r->dir, unit_vec(sub_vec(r->pos, s->spheres[i].pos))));
		r->hit_object = &s->spheres[i];;
	}
}

/**
 * adds scalar to rgba. clamps rgba values to 0 - 255 using int.
 * used for lighting
 */
void	light_rgba(t_rgba *colour, double scalar)
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

/**
 * scales rgba with multiplication by the scalar
 */
void	scale_rgba(t_rgba *colour, double scalar)
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

/**
 * gets light colour value including shadow
 */
void	get_light(t_ray *r, t_scene *s)
{
	int i;
	t_ray light_ray;
	double light_dis;
	if (s->n_lights == 0)
		light_rgba(&r->hit_colour, -255);
	i = -1;
	while (++i < s->n_lights)
	{
		light_ray.pos = r->hit_pos;
		light_ray.dir = unit_vec(sub_vec(r->hit_pos, s->lights[i].pos));

		check_colliders(&light_ray, s, r->hit_object);
		light_dis = get_distance(s->lights[i].pos, light_ray.pos);
		if (light_ray.t > 0 )
		{
			double angle = get_angle(s->lights[i].pos, r->hit_pos) - get_angle(r->hit_dir, r->hit_pos);
			double result = ((angle * -180) - get_distance(s->lights[i].pos, r->hit_pos)) * (-(s->lights[i].brightness - 1) + .5);
			light_rgba(&r->hit_colour, result * 1);
		}
		else
			light_rgba(&r->hit_colour, -255);
		(void)light_dis;
	}
}

/**
 * multiplys the two colours by .75 and then adds them together then clamps the values to 0-255
 */
t_rgba add_rgba(t_rgba Colour_A, t_rgba Colour_B)
{
	t_rgba new;
	int	r;
	int	g;
	int	b;

	// new.r = (ColourA.r * .5) + (ColourB.r * .5);
	// new.g = (ColourA.g * .5) + (ColourB.g * .5);
	// new.b = (ColourA.b * .5) + (ColourB.b * .5);

	r = (Colour_A.r * .75) + (Colour_B.r * .75);
	g = (Colour_A.g * .75) + (Colour_B.g * .75);
	b = (Colour_A.b * .75) + (Colour_B.b * .75);

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

/**
 * calculates the ray collider and configs the ray then calculates the lighting/colour
 */
void	ray_colour(t_ray *r, t_scene *s)
{
	r->hit_object = NULL;
	check_colliders(r, s, NULL);
	r->hit_colour = r->colour;
	if (r->t == DBL_MAX)
	{
		r->colour.r = 0;
		r->colour.g = 0;
		r->colour.b = 0;
		scale_rgba(&r->colour, s->ambient_light.ambient);
	}
	else
	{
		scale_rgba(&r->colour, s->ambient_light.ambient);
		get_light(r, s);
		r->colour = add_rgba(r->colour, r->hit_colour);
	}
}
