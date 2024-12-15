#include "cube.h"
#include "stb/stb_image.h"

Cube::Cube(glm::vec3 const position, glm::vec3 const size)
{
	this->position = position;
	this->eulers = glm::vec3 { 0.0f, 0.0f, 0.0f };

	make_texture();
	make_mesh(size.x, size.y, size.z);
}

Cube::~Cube()
{
    glDeleteBuffers(1, &vertex_buffer);
    glDeleteVertexArrays(1, &vertex_array);
    glDeleteTextures(1, &texture);
}

void Cube::update(float const dt)
{
    eulers += 1.0f * dt;
    if (eulers.z > 360)
    {
        eulers.z -= 360;
    }
}

void Cube::draw(OpenGlId const shader)
{
    glUseProgram(shader);

    // model transform
    glm::mat4 model { 1.0f };
    model = glm::translate(model, position);
    model = glm::rotate(model, glm::radians(eulers.z), { 0.0f, 0.0f, 1.0f });
    glUniformMatrix4fv(glGetUniformLocation(shader, "model"), 1, GL_FALSE, value_ptr(model));

    // mesh
    glBindVertexArray(vertex_array);

    // texture
    glBindTexture(GL_TEXTURE_2D, texture);

    glDrawArrays(GL_TRIANGLES, 0, 36);
}

void Cube::make_texture()
{
	int width, height, channels;
	unsigned char* data = stbi_load("img/ainsley.jpg", &width, &height, &channels, STBI_rgb_alpha);

	// make texture
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	// send data to gpu
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

	stbi_image_free(data);

	// configure sampler
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

void Cube::make_mesh(float const l, float const w, float const h)
{
    std::vector<float> vertices {
        l,  w, -h, 1.0f, 1.0f,
        l, -w, -h, 1.0f, 0.0f,
        -l, -w, -h, 0.0f, 0.0f,
        -l, -w, -h, 0.0f, 0.0f,
        -l,  w, -h, 0.0f, 1.0f,
        l,  w, -h, 1.0f, 1.0f,

        -l, -w,  h, 0.0f, 0.0f,
        l, -w,  h, 1.0f, 0.0f,
        l,  w,  h, 1.0f, 1.0f,
        l,  w,  h, 1.0f, 1.0f,
        -l,  w,  h, 0.0f, 1.0f,
        -l, -w,  h, 0.0f, 0.0f,

        -l,  w,  h, 1.0f, 1.0f,
        -l,  w, -h, 1.0f, 0.0f,
        -l, -w, -h, 0.0f, 0.0f,
        -l, -w, -h, 0.0f, 0.0f,
        -l, -w,  h, 0.0f, 1.0f,
        -l,  w,  h, 1.0f, 1.0f,

        l, -w, -h, 0.0f, 0.0f,
        l,  w, -h, 1.0f, 0.0f,
        l,  w,  h, 1.0f, 1.0f,
        l,  w,  h, 1.0f, 1.0f,
        l, -w,  h, 0.0f, 1.0f,
        l, -w, -h, 0.0f, 0.0f,

        -l, -w, -h, 0.0f, 0.0f,
        l, -w, -h, 1.0f, 0.0f,
        l, -w,  h, 1.0f, 1.0f,  
        l, -w,  h, 1.0f, 1.0f,
        -l, -w,  h, 0.0f, 1.0f,
        -l, -w, -h, 0.0f, 0.0f,

        l,  w,  h, 1.0f, 1.0f,
        l,  w, -h, 1.0f, 0.0f,
        -l,  w, -h, 0.0f, 0.0f, 
        -l,  w, -h, 0.0f, 0.0f,
        -l,  w,  h, 0.0f, 1.0f,
        l,  w,  h, 1.0f, 1.0f
    };

    glGenVertexArrays(1, &vertex_array);
    glBindVertexArray(vertex_array);

    glGenBuffers(1, &vertex_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

    // position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5*sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // texture coordinates
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5*sizeof(float), (void*)12);
    glEnableVertexAttribArray(1);
}
