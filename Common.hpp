#pragma once

// Include standard headers
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <math.h>

// Include GLEW
#define GLEW_STATIC
#include <GL/glew.h>

// Include GLM
#include <glm/glm.hpp>
using namespace glm;

#define WINDOW_WIDTH  ( 1500 )
#define WINDOW_HEIGHT ( 900 )

#define CNT_OF_ARRAY( a ) ( sizeof( a ) / sizeof( a[0] ) )

#define DEGREE_TO_RADIANS ( 3.14f / 180.0f )

#define PRINT_VEC( vec ) std::cout << "( " << vec[0] << ", " << vec[1] << " )\n"


/* Position Calculation s = s0 + v0t + 0.5at^2 */
#define KINETIC_EQ( pos, velo, accel, deltaTime ) ( pos )                                 \
                                                + ( velo * deltaTime )                    \
                                                + ( 0.5f * accel * deltaTime * deltaTime );
