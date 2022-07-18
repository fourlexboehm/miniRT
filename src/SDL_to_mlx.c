#include "../includes/minirt.h"

const int SCREEN_WIDTH = 1000;
const int SCREEN_HEIGHT = 1000;

typedef struct s_ray
{
	t_vector3	O;
	t_vector3	D;
	int			t;
} t_ray;
typedef struct s_cam
{
	t_vector3	O;
	double		Dx;
	double		Dy;
	double		fov;
} t_cam;

typedef struct s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
}	t_data;

typedef struct s_vars{
	void	*mlx;
	void	*win;
	t_data	img;
}	t_vars;

//------------------------------------------------------------------------ Vector Math ------------------------------------------------------

void printf_vector3(char c, t_vector3* v1)
{
	printf("%c = %lfx, %lfy, %lfz\n", c, v1->x, v1->y, v1->z);
}

t_vector3	add_vector3(const t_vector3 v1, const t_vector3 v2)
{
	t_vector3	ret;

	ret.x = v1.x + v2.x;
	ret.y = v1.y + v2.y;
	ret.z = v1.z + v2.z;
	return (ret);
}
t_vector3	scale_vector3(const t_vector3 vec, const double scale)
{
	t_vector3	new_vec;

	new_vec.x = vec.x * scale;
	new_vec.y = vec.y * scale;
	new_vec.z = vec.z * scale;
	return (new_vec);
}
t_vector3	div_vector3(const t_vector3 vec, const double scale)
{
	t_vector3	new_vec;

	new_vec.x = vec.x / scale;
	new_vec.y = vec.y / scale;
	new_vec.z = vec.z / scale;
	return (new_vec);
}

t_vector3	subtract_vector3(const t_vector3 v1, const t_vector3 v2)
{
	t_vector3	ret;

	ret.x = v1.x - v2.x;
	ret.y = v1.y - v2.y;
	ret.z = v1.z - v2.z;
	return (ret);
}

void	init_vec3(t_vector3 *v, double x, double y, double z)
{
	v->x = x;
	v->y = y;
	v->z = z;
}

t_vector3 at(t_ray* ray, double t)
{
	return (add_vector3(ray->O, scale_vector3(ray->D, t)));
}

t_vector3 unit_vector3(t_vector3 v1)
{
	double mag = sqrt((v1.x * v1.x) + (v1.y * v1.y) + (v1.z * v1.z));
	v1.x /= mag;
	v1.y /= mag;
	v1.z /= mag;
	return (v1);
}

double dot(t_vector3 v1, t_vector3 v2)
{
	return ((v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z));
}

double length_squared(t_vector3 const v3)
{
	return (v3.x * v3.x + v3.y * v3.y + v3.z * v3.z);
}

double length(t_vector3 const v3)
{
	return sqrt(length_squared(v3));
}

t_vector3 new_vector3(double x, double y, double z)
{
	t_vector3 rtn;
	rtn.x = x;
	rtn.y = y;
	rtn.z = z;
	return (rtn);
}

//--------------------------------------------------------------------------------- sphere colliders ---------------------------------------------

float collide_sphere_3D(t_ray* r, t_sp* s)
{
	t_vector3 oc = subtract_vector3(r->O, s->pos);
	float a = length_squared(r->D);
	float b = dot(oc, r->D);
	float c = length_squared(oc) - s->diameter * s->diameter;
	float discriminant = (b * b) - (a * c);
	if (discriminant < 0)
		return (-1);
	else
		return ((-b - sqrt(discriminant)) / a);
}

//--------------------------------------------------------------------------------------------------- ray color / reflect ------------------------------------

t_vector3 reflect(t_vector3 v, t_vector3 n)
{
	return subtract_vector3(v, scale_vector3(n, 2 * dot(v, n)));
}

t_vector3 ray_color(t_ray *r, double movex, double movez)
{
	double mod = 2;

	t_vector3 color;
	color.x = 1;
	color.y = 0;
	color.z = 0;

	t_sp sp;
	sp.pos.x = 0;
	sp.pos.y = 0;
	sp.pos.z = 3;
	sp.diameter = 1;

	t_sp sp2;
	sp2.pos.x = movex;
	sp2.pos.y = 1;
	sp2.pos.z = movez;
	sp2.diameter = 1;

	float t = collide_sphere_3D(r, &sp);
	float t2 = collide_sphere_3D(r, &sp2);

	t_pl pl;
	pl.pos = new_vector3(0,0, 10);
	pl.rot = unit_vector3(new_vector3(0, 0, 90));

	t_pl pl2;
	pl2.pos = new_vector3(0, 3, 10);
	pl2.rot = unit_vector3(new_vector3(0, 100, 90));

	double d;

	if (t < 0 && t2 > 0)
		return (new_vector3(0, 0, 255));


	if (t > 0)
	{
		t_ray ref;
		t_vector3 out_N;
		ref.O = at(r, t);

		out_N = unit_vector3(subtract_vector3(ref.O, sp.pos)); 

		ref.D = reflect(unit_vector3(r->D), out_N);

		t = collide_sphere_3D(&ref, &sp2);

		if (t > 0)
			return (new_vector3(0, 0, 128));

		d = dot(unit_vector3(ref.D), pl.rot);
		if (fabs(d) > 0)
		{
			//t_vector3 difference = subtract_vector3(pl.pos, r->O);
			t = dot(subtract_vector3(pl.pos, ref.O), pl.rot) / d;
			//t = dot(difference, pl.rot) / d;
		}

		d = dot(pl2.rot, ref.D);
		if (fabs(d) > 0)
		{
			//t_vector3 difference = subtract_vector3(pl2.pos, r->O);
			t2 = dot(subtract_vector3(pl2.pos, ref.O), pl2.rot) / d;
			//t2 = dot(difference, pl2.rot) / d;
		}


		if (t > 0 && t < t2)
			return (new_vector3(128, 0, t * 5));
		else if (t2 > 0 && t2 < t)
			return (new_vector3(128, (t * 5) - 10, 0));
			
			return (new_vector3(0, 255, 0));
		}

	

	// t = dot(subtract_vector3(pl.pos, r->O), pl.rot) / dot(r->D, pl.rot);
	// t2 = dot(subtract_vector3(pl2.pos, r->O), pl2.rot) / dot(r->D, pl2.rot);
	
	d = dot(unit_vector3(r->D), pl.rot);
	if (fabs(d) > 0)
	{
		//t_vector3 difference = subtract_vector3(pl.pos, r->O);
		t = dot(subtract_vector3(pl.pos, r->O), pl.rot) / d;
		//t = dot(difference, pl.rot) / d;
	}

	d = dot(pl2.rot, r->D);
	if (fabs(d) > 0)
	{
		//t_vector3 difference = subtract_vector3(pl2.pos, r->O);
		t2 = dot(subtract_vector3(pl2.pos, r->O), pl2.rot) / d;
		//t2 = dot(difference, pl2.rot) / d;
	}


	if (t > 0 && t < t2)
		return (new_vector3(128, 0, t * 5));
	else if (t2 > 0 && t2 < t)
		return (new_vector3(128, (t * 5) - 10, 0));


	return (new_vector3(0, 0, 0));
}

//--------------------------------------------------------------------------------------------------- Frame Render

void	pixel_put(t_data *r, int x, int y, int color);
int		create_trgb(int t, int r, int g, int b);

void render_frame(t_data* img)
{

	t_cam cam;
	cam.O.x = 0;
	cam.O.y = 0;
	cam.O.z = -3;
	cam.Dx = 0;
	cam.Dy = 0;
	cam.fov = 20;

	t_ray ray;
	ray.O.x = cam.O.x;
	ray.O.y = cam.O.y;
	ray.O.z = cam.O.z;
	ray.D.z = 0;
	ray.t = 1000;
	t_vector3 color;

	double aspect_ratio = SCREEN_WIDTH / SCREEN_HEIGHT;

	double viewport_height = 2.0;
	double viewport_width = aspect_ratio * viewport_height;
	double focal_length = 1.0;

	t_vector3 origin; init_vec3(&origin, 0, 0, 0);
	t_vector3 horizontal; init_vec3(&horizontal, viewport_width, 0, 0);
	t_vector3 vertical; init_vec3(&vertical, 0, viewport_height, 0);
	t_vector3 focal; init_vec3(&focal, 0, 0, focal_length);
	t_vector3 lower_left_corner = subtract_vector3(subtract_vector3(origin, scale_vector3(horizontal, 0.5)), subtract_vector3(scale_vector3(vertical, 0.5), focal));

	static double movex = 3;
	static double movez = 3;
	for (int y = SCREEN_HEIGHT; y >= 0; --y) {
		for (int x = 0; x < SCREEN_WIDTH; ++x) {
			double u = (double)x / SCREEN_WIDTH;
			double v = (double)y / SCREEN_HEIGHT;

			ray.D = subtract_vector3(add_vector3(add_vector3(lower_left_corner, scale_vector3(horizontal, u)), scale_vector3(vertical, v)), origin);
			color = ray_color(&ray, movex, movez);
			pixel_put(img, x, y, create_trgb(0, color.x, color.y, color.z));
		}
	}
	static double angle = 0;
	movex = 3 * cos(angle);
	movez = 3 * sin(angle) + 3;
	angle -= 0.2;
	printf("movex = %lf\n", movex);
	printf("movez = %lf\n\n", movez);
}

//--------------------------------------------------------------------------------------------------- mlx functions ---------------------------------------------

static int	key_hook(int keycode)
{
	if (keycode == KEY_ESC)
		exit(0);
	return (0);
}
void	pixel_put(t_data *r, int x, int y, int color)
{
	char	*dst;

	dst = r->addr + (y * r->line_length + x * (r->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}
int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

typedef struct s_sce
{
	t_cam	*cam;
	t_vars	*vars;
	double	t;
} t_sce;


int	next_frame(t_vars *v)
{
	int		endian;
	t_data	img;
	img.img = mlx_new_image(v->mlx, SCREEN_HEIGHT + 1, SCREEN_WIDTH + 1);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &endian);


	render_frame(&img);
	mlx_put_image_to_window(v->mlx, v->win, img.img, 0, 0);
	mlx_destroy_image(v->mlx, img.img);
	return(1);
}

int main(void)
{
	t_vars	v;

	v.mlx = mlx_init();
	v.win = mlx_new_window(v.mlx, SCREEN_WIDTH, SCREEN_HEIGHT, MLX_TITLE);

	mlx_loop_hook(v.mlx, next_frame, &v);
	mlx_key_hook(v.win, key_hook, &v);
	mlx_loop(v.mlx);
}