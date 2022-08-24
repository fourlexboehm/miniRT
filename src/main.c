#include "../includes/minirt.h"

int	main(int argc, char **argv)
{
	char		**line;
	t_scene		scene;
	t_vector3	**v_matrix;
	int			**c_matrix;
	char 		*file;

	if (argc == 2)
	{
		file = ft_strjoin("scenes/", argv[1]);
		line = get_file(file);
		free(file);
	}
	else
		line = get_file("scenes/subject_example2.rt");
	assign_scene(&scene, line);
	v_matrix = calculate_viewport_vectors(scene.camera);
	c_matrix = set_colour_matrix(v_matrix, scene);
	//free v_matrix TODO
	render_image_on_mlx(c_matrix);
}