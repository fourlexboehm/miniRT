#include "../includes/minirt.h"

t_vector3	reflect(t_vector3 v, t_vector3 n)
{
	return (subtract_vector3(v, scale_vector3(n, 2 * dot(v, n))));
}

// angle = arccos[(xa * xb + ya * yb + za * zb) / (√(xa2 + ya2 + za2) * √(xb2 + yb2 + zb2))]
// angle = arccos{[(x2 - x1) * (x4 - x3) + (y2 - y1) * (y4 - y3) + (z2 - z1) * (z4 - z3)] / [√((x2 - x1)2 + (y2 - y1)2+ (z2 - z1)2) * √((x4 - x3)2 + (y4 - y3)2 + (z4 - z3)2)]}
double getAngle(t_vector3 a, t_vector3 b)
{
	//printf("a = %lf\n", sqrt( a.x * a.x + a.y * a.y + a.z * a.z ));
	//printf("b = %lf\n", sqrt( b.x * b.x + b.y * b.y + b.z * b.z ));
	return (acos( dot(a, b) / ((sqrt( a.x * a.x + a.y * a.y + a.z * a.z ) + 0.0001) * ( sqrt( b.x * b.x + b.y * b.y + b.z * b.z )))));
}

static void	getHitcircle(t_ray* r, t_sp* s)
{
	r->hitO = at(r, r->t);
	r->hitD = unit_vector3(reflect(r->D, unit_vector3(subtract_vector3(r->O, s->pos))));
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
			getHitcircle(r, &s->spheres[i]);
		}
	}
	i = -1;
	while (++i < s->n_planes)
	{
		t = collide_plane(r, &s->planes[i]);
		if (t < r->t)
		{
			r->t = t;
			//r->colour = s->planes[i].colour;
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

void	scale_color(t_rgba *colour, double scalar)
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

void	get_light(t_ray *r, t_scene *s)
{
	int	i;

	i = -1;
	while (++i < s->n_lights)
	{
		double angle = getAngle(s->lights[i].pos, r->hitO) - getAngle(r->hitD, r->hitO);
		//double unit_result  = angle / M_PI * 2;
		double result = (angle * 180) * -1; 
		if (result == 90)
			printf("================================\n");
		if (result > -1)
			scale_color(&r->colour, result);
		//printf("angle = %lf\n", angle * 180 / 3.14);
		//r->colour.r += angle * 180 / 3.14;
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
