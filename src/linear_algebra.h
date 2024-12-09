#include "config.h"


struct mat4
{
	float entries[16] = { 0 };  // zero-initialized
};

struct vec3
{
	float entries[3] = { 0 };  // zero-initialized
};

mat4 create_identity4();

mat4 create_translation(vec3 const translation_vec);

mat4 create_rotation_x(float const angle);

mat4 create_rotation_y(float const angle);

mat4 create_rotation_z(float const angle);

mat4 prod(mat4 const A, mat4 const B);