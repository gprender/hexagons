#include "config.h"

/**
 * types 
 */

struct mat4
{
	float entries[16] = { 0 };  // zero-initialized
};

struct vec3
{
	float entries[3] = { 0 };  // zero-initialized
};

/**
 * vector operations
 */

vec3 scale(vec3 const v, float const scalar);

float dot_prod(vec3 const u, vec3 const v);

vec3 normalize(vec3 const v);

vec3 cross_prod(vec3 const u, vec3 const v);

/**
 * matrix operations 
 */

mat4 create_identity4();

mat4 create_translation(vec3 const translation_vec);

mat4 create_rotation_x(float const angle);

mat4 create_rotation_y(float const angle);

mat4 create_rotation_z(float const angle);

mat4 create_look_at(vec3 from, vec3 to);

mat4 prod(mat4 const A, mat4 const B);
