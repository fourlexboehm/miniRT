#include "../../includes/minirt.h"

/**
 * https://www.w3adda.com/c-programs/c-program-to-solve-second-order-quadratic-equation
 */
int	second_degree_equation(double a, double b, double c, double d[2])
{
	float	inside_sqrt;

	if (a == 0.0 || powf(b, 2.0) < 4.0 * a * c)
		return (0);
	inside_sqrt = powf(b, 2.0) - (4.0 * a * c);
	d[0] = (-b + sqrtf(inside_sqrt)) / (2.0 * a);
	d[1] = (-b - sqrtf(inside_sqrt)) / (2.0 * a);
	return (1);
}
