#include <cmath>

#include "linear_algebra.h"


float const PI = 3.14159;

mat4 create_identity4()
{
	mat4 m;

	m.entries[0] = 1.0f;
	m.entries[5] = 1.0f;
	m.entries[10] = 1.0f;
	m.entries[15] = 1.0f;

	return m;
}

mat4 create_translation(vec3 const translation_vec)
{
	mat4 m = create_identity4();

	m.entries[12]	= translation_vec.entries[0];
	m.entries[13]	= translation_vec.entries[1];
	m.entries[14]	= translation_vec.entries[2];

	return m;
}

mat4 create_rotation_x(float const angle)
{
	float const angle_rad = angle * (PI / 180.0f);
	float const cos_angle = cosf(angle_rad);
	float const sin_angle = sinf(angle_rad);

	mat4 m = create_identity4();

	m.entries[5] = cos_angle;
	m.entries[6] = sin_angle;

	m.entries[9] = -sin_angle;
	m.entries[10] = cos_angle;

	return m;
}

mat4 create_rotation_y(float const angle)
{
	float const angle_rad = angle * (PI / 180.0f);
	float const cos_angle = cosf(angle_rad);
	float const sin_angle = sinf(angle_rad);

	mat4 m = create_identity4();

	m.entries[0] = cos_angle;
	m.entries[2] = -sin_angle;

	m.entries[8] = sin_angle;
	m.entries[10] = cos_angle;

	return m;
}

mat4 create_rotation_z(float const angle)
{
	float const angle_rad = angle * (PI / 180.0f);
	float const cos_angle = cosf(angle_rad);
	float const sin_angle = sinf(angle_rad);

	mat4 m = create_identity4();

	m.entries[0] = cos_angle;
	m.entries[1] = sin_angle;

	m.entries[4] = -sin_angle;
	m.entries[5] = cos_angle;

	return m;
}

// Pretty sure something is broken in this one
mat4 prod(mat4 const A, mat4 const B)
{
	mat4 C;

	for (int i = 0; i < 4; i++) // column
	{
		for (int j = 0; j < 4; j++)  // row
		{
			float c_ij = 0;

			for (int k = 0; k < 4; k++)
			{
				c_ij += A.entries[i+k] * B.entries[j+(k*4)];
			}

			C.entries[(i*4)+j] = c_ij;
		}
	}

	return C;
}
