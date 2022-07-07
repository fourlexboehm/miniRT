
#define PI 3.14
#include "../includes/minirt.h"

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

//------------------------------------------------------------------------------------------


int dot(t_vector3 *v1, t_vector3 *v2)
{
	return ((v1->x * v2->x) + (v1->y * v2->y) + (v1->z * v2->z));
}

double collide_sphere_3D(t_ray* ray, t_sp* s)
{
	double t;
	double t1;
	t_vector3 temp;


	temp = subtract_vector3(s->pos, ray->O);
	t = dot(&temp, &ray->D);

	double x;
	double y;
	t_vector3 p;

	p = scale_vector3(add_vector3(ray->O, ray->D), ray->t);

	temp = subtract_vector3(p, s->pos);
	y = get_distance_vector3(&ray->O, &temp);
	if (y < s->diameter)
	{
		x = sqrt((s->diameter * s->diameter) - (y * y));
		t1 = t - x;
		return (y / 55);
	}
	return (0);
}


//------------------------------------------------------------------------------------------

static int	key_hook(int keycode, t_vars *vars)
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
void render_frame(t_data* renderer, t_sp *sp, t_cam *cam)
{
	t_ray ray;
	double	color;
	double	color2;
	ray.O.x = cam->O.x;
	ray.O.y = cam->O.y;
	ray.O.z = cam->O.z;
	ray.D.z = 0;
	ray.D.y = cam->Dy - (cam->fov * .5);
	ray.t = 10000;

	for (int y = 0; y < 1000; y++)
	{
		ray.D.x = cam->Dx - (cam->fov * .5);
		for (int x = 0; x < 1000; x++)
		{
			color2 = 0;
			for (int i = 0; i < 2; i++)
			{
				color = collide_sphere_3D(&ray, &sp[i]);
				if (color > 0 && (color < color2 || color2 == 0)  && i == 0)
					color2 = color * ((10 * i) + 1);
				else if (color > 0 && (color < color2 || color2 == 0)  && i == 1)
					color2 = create_trgb(0, color, 0, 0);
			}
			if (color2 > 0)
					pixel_put(renderer, x, y, color2);
			ray.D.x += cam->fov / 1000;
		}
		ray.D.y += cam->fov / 1000;
		printf("\rprogress...%d%%", y / 10 + 1);
	}
	printf("\nrender done\n");
}

typedef struct s_sce
{
	t_cam	*cam;
	t_sp	*sp;
	t_vars	*vars;
	double	t;
} t_sce;


int	next_frame(t_sce *all)
{
	int		endian;
	all->t += 0.01;
	// all->sp[1].pos.x = 15000 * cos(all->t);
	// all->sp[1].pos.z = 15000 * sin(all->t);

	all->vars->img.img = mlx_new_image(all->vars->mlx, 1000, 1000);
	all->vars->img.addr = mlx_get_data_addr(all->vars->img.img, &all->vars->img.bits_per_pixel,
			&all->vars->img.line_length, &endian);

	render_frame(&all->vars->img, all->sp, all->cam);
	mlx_put_image_to_window(all->vars->mlx, all->vars->win, all->vars->img.img, 0, 0);
	return(1);
}

int main(void)
{
	t_vars	v;
	int		endian;
	t_sce	all;

    t_cam cam;
	cam.O.x = 0;
	cam.O.y = 0;
	cam.O.z = 0;
	cam.Dx = 0;
	cam.Dy = 0;
	cam.fov = 45;

	t_sp *sp;
	sp = malloc(sizeof(t_sp) * 2);
	sp[0].pos.x = 0;
	sp[0].pos.y = 0;
	sp[0].pos.z = 0;
	sp[0].diameter = 10000;

	sp[1].pos.x = 15000;
	sp[1].pos.y = 0;
	sp[1].pos.z = 0;
	sp[1].diameter = 10000;

	all.cam = &cam;
	all.sp = sp;

	v.mlx = mlx_init();
	v.win = mlx_new_window(v.mlx, 1000, 1000, MLX_TITLE);
	v.img.img = mlx_new_image(v.mlx, 1000, 1000);
	v.img.addr = mlx_get_data_addr(v.img.img, &v.img.bits_per_pixel,
			&v.img.line_length, &endian);
	
	all.vars = &v;
	mlx_loop_hook(v.mlx, next_frame, &all);
	mlx_key_hook(v.win, key_hook, &v);
	mlx_loop(v.mlx);
}