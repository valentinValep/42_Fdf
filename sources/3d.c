#include <math.h>
#include "fdf.h"

t_point	projection(t_point point)
{
	t_point	res;

	res.z = 0;
	res.x = (sqrt(2.) / 2) * (point.x - point.y) + WINDOW_WIDTH / 2;
	res.y = (1. / sqrt(6.)) * (point.x + point.y) - sqrt(2. / 3.) * point.z;
	return (res);
}

t_point	rotate(t_point point, char axis_flag, double degree)
{
	if (axis_flag & X_AXIS)
	{
		point.y = point.y * cos((double) degree)
			+ point.z * (-sin((double) degree));
		point.z = point.z * cos((double) degree);
	}
	if (axis_flag & Y_AXIS)
	{
		point.x = point.x * cos((double) degree)
			+ point.z * sin((double) degree);
		point.z = point.x * (-sin((double) degree))
			+ point.z * cos((double) degree);
	}
	if (axis_flag & Z_AXIS)
	{
		point.x = point.x * cos((double) degree)
			+ point.y * (-sin((double) degree));
		point.y = point.x * sin((double) degree)
			+ point.y * cos((double) degree);
	}
	return (point);
}
