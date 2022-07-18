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

t_vector3	div_vector3(const t_vector3 vec, const double scale)
{
	t_vector3	new_vec;

	new_vec.x = vec.x / scale;
	new_vec.y = vec.y / scale;
	new_vec.z = vec.z / scale;
	return (new_vec);
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

double get_distance_vector3(t_vector3 *v1, t_vector3 *v2)
{
	return(sqrt(pow(v2->x - v1->x, 2)
			  + pow(v2->y - v1->y, 2)
			  + pow(v2->z + v1->z, 2)));
}
