
#define PI 3.141592654

typedef struct s_vector3
{
	int	x;
	int	y;
	int	z;
} t_vector3;

typedef	struct s_sp
{
	t_vector3	pos;
	double		diameter;
}	t_sp;

typedef struct s_ray
{
	t_vector3	O;
	double		D;
} t_ray;

double	get_angle_deg(t_vector3* v1, t_vector3* v2)
{
	return (atan((v1->y - v2->y) / (v1->x - v2->x)) * 180 / PI);
}

double	get_angle_rad(t_vector3* v1, t_vector3* v2)
{
	return (atan(v1->y - v2->y) / (v1->x - v2->x));
}

double get_coord_deg_vector3(t_vector3* v1, t_vector3* v2)
{
	return (get_coord_rad_vector3(v1, v2) * 180 / 3.141592);
}

void draw_circle(SDL_Renderer* r, t_sp* s)
{
	int	i;

	SDL_SetRenderDrawColor(r, 0, 0, 255, 255);
	i = 0;
	while (++i < 1000)
		SDL_RenderDrawPoint(r, s->pos.x + cos(i * 3.14 / 180) * s->diameter, s->pos.y + sin(i * 3.14 / 180) * s->diameter);
}

void	draw_ray(SDL_Renderer* r, t_ray* ray)
{
	//SDL_SetRenderDrawColor(r, 0, 255, 0, 255);
	int	x = ray->O.x + cos(ray->D * 3.14 / 180) * 1000;
	int	y = ray->O.y + sin(ray->D * 3.14 / 180) * 1000;
	SDL_RenderDrawLine(r, ray->O.x, ray->O.y, x, y);
}

int collide_sphere(t_ray *ray, t_sp *s, SDL_Renderer *r)
{
	double	A;
	double	angle;
	double	hypo;
	double	adj;

	adj = get_distance_vector3(&ray->O, &s->pos);
	angle = get_angle_deg(&ray->O, &s->pos) - ray->D;
	A = tan(angle * PI / 180) * adj;
	if (A < 0)
		A *= -1;
	if (A < s->diameter)
	{
		printf("HIT!!!\n");
		t_ray hit;
		double	n;
		double	d;

		double h = sqrt(pow(s->diameter, 2) - pow(A, 2));

		hit.O.x = ray->O.x + cos(ray->D * 3.14 / 180) * (adj - h);
		hit.O.y = ray->O.y + sin(ray->D * 3.14 / 180) * (adj - h);
		n = (atan(fabs(hit.O.y - s->pos.y) / fabs(hit.O.x - s->pos.x)) * 180 / PI) + 180;
		//hit.D = (atan(fabs(hit.O.y - s->pos.y) / fabs(hit.O.x - s->pos.x)) * 180 / PI) + 180;
		hit.D = abs(ray->D - n) * 2;
		printf("hit D = %lf\n", hit.D);
		SDL_SetRenderDrawColor(r, 0, 0, 255, 255);
		draw_ray(r, &hit);
		return (1);
	}
	else
		return (0);
}
