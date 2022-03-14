#pragma once

#include "Common.hpp"
#include "Planet.hpp"
#include "Rocket.hpp"

class RocketProjection
{
private:
    GLuint program;
    GLuint VAO;
    GLuint VBO;

    // Uniforms
    GLuint colorLoc;

    glm::vec2 verts[30];

public:
    RocketProjection();
    void Draw();
    void CalculatePath( Rocket &rocket, Planet &planet );
};

