#include <cmath>

#include "linear_algebra.h"


float const PI = 3.14159;

/**
 * vector operations
 */

vec3 scale(vec3 const v, float const scalar)
{
	return vec3 {
		v.entries[0] * scalar,
		v.entries[1] * scalar,
		v.entries[2] * scalar
	};
}

float dot_prod(vec3 const u, vec3 const v)
{
	return (
		u.entries[0] * v.entries[0]
		+ u.entries[1] * v.entries[1]
		+ u.entries[2] * v.entries[2]
	);
}

vec3 normalize(vec3 const v)
{
	float magnitude = sqrtf(dot_prod(v, v));
	vec3 u = scale(v, 1/magnitude);
	return u;
}

vec3 cross_prod(vec3 const u, vec3 const v)
{
	vec3 w;

	w.entries[0] = u.entries[1] * v.entries[2] - u.entries[2] * v.entries[1];
	w.entries[1] = -(u.entries[2] * v.entries[0] - u.entries[0] * v.entries[2]);
	w.entries[2] = u.entries[0] * v.entries[1] - u.entries[1] * v.entries[0];

	return w;
}


/**
 * matrix operations 
 */

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

mat4 create_look_at(vec3 from, vec3 to)
{
	vec3 global_up { 0.0f, 0.0f, 1.0f };

	vec3 forward {
		to.entries[0] - from.entries[0],
		to.entries[1] - from.entries[1],
		to.entries[2] - from.entries[2]
	};
	forward = normalize(forward);

	vec3 right = normalize(cross_prod(forward, global_up));
	vec3 up = normalize(cross_prod(right, forward));

	mat4 m;

	m.entries[0] = right.entries[0];
	m.entries[1] = up.entries[0];
	m.entries[2] = -forward.entries[0];
	m.entries[3] = 0.0f;

	m.entries[4] = right.entries[1];
	m.entries[5] = up.entries[1];
	m.entries[6] = -forward.entries[1];
	m.entries[7] = 0.0f;

	m.entries[8] = right.entries[2];
	m.entries[9] = up.entries[2];
	m.entries[10] = -forward.entries[2];
	m.entries[11] = 0.0f;

	m.entries[12] = -dot_prod(right, from);
	m.entries[13] = -dot_prod(up, from);
	m.entries[14] = dot_prod(forward, from);
	m.entries[15] = 1.0f;

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
