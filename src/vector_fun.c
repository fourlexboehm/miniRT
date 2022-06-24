#include "../includes/minirt.h"

/**
 * @brief      Scales a vector by a scalar.
 * @param vec
 * @param scale
 * @return
 */

t_vector3	scale_vector3(const t_vector3 vec, const double scale)
{
	t_vector3	new_vec;

	new_vec.x = vec.x * scale;
	new_vec.y = vec.y * scale;
	new_vec.z = vec.z * scale;
	return (new_vec);
}

t_vector3	add_vector3(const t_vector3 v1, const t_vector3 v2)
{
	t_vector3	ret;

	ret.x = v1.x + v2.x;
	ret.y = v1.y + v2.y;
	ret.z = v1.z + v2.z;
	return (ret);
}

t_vector3	subtract_vector3(const t_vector3 v1, const t_vector3 v2)
{
	t_vector3	ret;

	ret.x = v1.x - v2.x;
	ret.y = v1.y - v2.y;
	ret.z = v1.z - v2.z;
	return (ret);
}

void	multi_vector3(t_vector3 *v1, t_vector3 *v2)
{
	v1->x *= v2->x;
	v1->y *= v2->y;
	v1->y *= v2->z;
}

double get_distance_vector3(t_vector3 *v1, t_vector3 *v2)
{
	return(sqrt(pow(v2->x - v1->x, 2)
			  + pow(v2->y - v1->y, 2)
			  + pow(v2->z + v1->z, 2)));
}

double get_distance_vector2(t_vector3 *v1, t_vector3 *v2)
{
	return(sqrt(pow(v2->x - v1->x, 2)
			  + pow(v2->y - v1->y, 2)));
}

double get_coord_rad_vector3(t_vector3 *v1, t_vector3 *v2)
{
	return (acos((v1->x * v2->x + v1->y * v2->y + v1->z * v2->z)
			/ ( sqrt( pow(v1->x, 2) + pow(v1->y, 2) + pow(v1->z, 2))
			* sqrt( pow(v2->x, 2) + pow(v2->y, 2) + pow(v2->z, 2)))));
}

double get_coord_deg_vector3(t_vector3 *v1, t_vector3 *v2)
{
	return (get_coord_rad_vector3(v1, v2) * (180 / 3.141592));
}