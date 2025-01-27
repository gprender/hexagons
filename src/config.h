/**
 * @author Graeme Prendergast
 */

#pragma once

#include <cstdint>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using OpenGlId = uint32_t;
using EntityId = uint32_t;

struct TransformComponent;
using TransformComponentMap_t = std::unordered_map<OpenGlId, TransformComponent>;

struct PhysicsComponent;
using PhysicsComponentMap_t = std::unordered_map<OpenGlId, PhysicsComponent>;

struct RenderComponent;
using RenderComponentMap_t = std::unordered_map<OpenGlId, RenderComponent>;
