/**
 * @author Graeme Prendergast
 */

#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using OpenGlId = uint32_t;

std::vector<std::string> split(std::string const& str, std::string const& delimiter);

std::string to_string(std::vector<std::string> const& vec);
