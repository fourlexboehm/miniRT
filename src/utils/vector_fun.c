#include "minirt.h"

/**
 * @brief      Scales a vector by a scalar.
 * @param vec
 * @param scale
 * @return
 */

/**
 * scales a vector with multiplication. returns result vector
 */
t_vec	scale_vec(const t_vec vec, const double scale)
{
	t_vec	new_vec;

	new_vec.x = vec.x * scale;
	new_vec.y = vec.y * scale;
	new_vec.z = vec.z * scale;
	return (new_vec);
}

/**
 * adds two vectors together. returns result vector
 */
t_vec	add_vec(const t_vec v1, const t_vec v2)
{
	t_vec	ret;

	ret.x = v1.x + v2.x;
	ret.y = v1.y + v2.y;
	ret.z = v1.z + v2.z;
	return (ret);
}

/**
 * subtracts the first vector with the second vector. returns result vector
 */
t_vec	sub_vec(const t_vec v1, const t_vec v2)
{
	t_vec	ret;

	ret.x = v1.x - v2.x;
	ret.y = v1.y - v2.y;
	ret.z = v1.z - v2.z;
	return (ret);
}

/**
 * divides the vector with the scale. returns result vector
 */
t_vec	div_vec(const t_vec vec, const double scale)
{
	t_vec	new_vec;

	new_vec.x = vec.x / scale;
	new_vec.y = vec.y / scale;
	new_vec.z = vec.z / scale;
	return (new_vec);
}

/**
 * edits vectors values with x,y,z
 */
void	init_vec(t_vec *v, double x, double y, double z)
{
	v->x = x;
	v->y = y;
	v->z = z;
}

/**
 * returns vector pos at result of ray dir and pos scaled with t 
 */
t_vec	at(t_ray *ray, double t)
{
	return (add_vec(ray->pos, scale_vec(ray->dir, t)));
}

/**
 * returns a unitized vector
 */
t_vec	unit_vec(t_vec v1)
{
	double	mag;

	mag = sqrt((v1.x * v1.x) + (v1.y * v1.y) + (v1.z * v1.z));
	v1.x /= mag;
	v1.y /= mag;
	v1.z /= mag;
	return (v1);
}

/**
 * reutrns a new vector with x,y,z input values
 */
t_vec new_vec(double x, double y, double z)
{
	t_vec rtn;
	rtn.x = x;
	rtn.y = y;
	rtn.z = z;
	return (rtn);
}

/**
 * returns distance between two vectors
 */
double get_distance(t_vec v1, t_vec v2)
{
	return(sqrt((pow(v2.x - v1.x, 2) + pow(v2.y - v1.y, 2) + pow(v2.z - v1.z, 2))));
}
