#pragma once

#include "Common.hpp"

class RocketProjection
{
private:
    GLuint program;
    GLuint VAO;
    GLuint VBO;

    glm::vec2 verts[10];

public:
    RocketProjection();
    void Draw();
    void CalculateVerts( glm::vec2 &pos, glm::vec2 &velo, glm::vec2 &accel );
};

