#pragma once

#include "Common.hpp"

GLuint LoadShader( const char* vertex_file_path, const char* fragment_file_path );

#define SHADER_ROCKET_VERT "shaders/rocket.vert"
#define SHADER_ROCKET_FRAG "shaders/rocket.frag"

#define SHADER_PLANET_VERT "shaders/planet.vert"
#define SHADER_PLANET_FRAG "shaders/planet.frag"
