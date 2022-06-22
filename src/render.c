
#include "../includes/minirt.h"

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

static	int	close_window(t_vars *vars)
{
	mlx_destroy_window(vars->mlx, vars->win);
	exit (0);
}

static void	render_pixels(t_data	*img, int **matrix_colors)
{
	int		x;
	int		y;
	char	*pixel;

	y = 0;
	while (y < WIN_HEIGHT)
	{
		x = 0;
		while (x < WIN_WIDTH)
		{
			pixel = (y * img->line_length + x * (img->bits_per_pixel / 8)) + img->addr;
			*(unsigned int *)pixel = matrix_colors[x][y];
			x++;
		}
		y++;
	}
	//function call to free matrix_colors
}

static int	key_hook(int keycode, t_vars *vars)
{
	if (keycode == KEY_ESC)
		close_window(vars);
	return (0);
}

/**
 * * Initialize mlx to render image following
 * https://harm-smits.github.io/42docs/libs/minilibx/getting_started.html
 * (writing-pixels-to-a-image)
 * @param matrix_colors	matrix of colors to render
*/
void	render_image_on_mlx(int	**matrix_colors)
{
	t_vars	v;
	int		endian;

	v.mlx = mlx_init();
	v.win = mlx_new_window(v.mlx, WIN_WIDTH, WIN_HEIGHT, MLX_TITLE);
	v.img.img = mlx_new_image(v.mlx, WIN_WIDTH, WIN_HEIGHT);
	v.img.addr = mlx_get_data_addr(v.img.img, &v.img.bits_per_pixel,
			&v.img.line_length, &endian);
	render_pixels(&v.img, matrix_colors);
	mlx_put_image_to_window(v.mlx, v.win, v.img.img, 0, 0);
	mlx_key_hook(v.win, key_hook, &v);
	mlx_hook(v.win, 17, 1L << 17, close_window, &v);
	mlx_loop(v.mlx);
}
